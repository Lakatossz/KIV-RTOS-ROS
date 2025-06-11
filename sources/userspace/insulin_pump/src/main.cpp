#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <monitor.h>
#include <drivers/gpio.h>
#include <temperature.h>
#include <cgm.h>
#include <rtc.h>

#include "../include/insulin_pump/insulin_pump/insulin_pump.hpp"
#include "../include/insulin_pump/pump_settings/pump_settings.hpp"

#include "../include/utils/logger/logger.hpp"

uint32_t logpipe;
uint32_t pump_settings_in_pipe;
uint32_t emergency_pipe;
uint32_t air_release_pipe;
uint32_t glycemia_context_pipe;

mutex_t ail_mutex;
mutex_t hw_error_mutex;
mutex_t sw_error_mutex;

CRtc::time_stamp time;

int main(int argc, char** argv)
{
	logpipe = pipe("log", 128);
	pump_settings_in_pipe = pipe("io_task_input", sizeof(pump_setting));
	emergency_pipe = pipe("io_task_input", sizeof(pump_setting));
	glycemia_context_pipe = pipe("glycemia_context", sizeof(glycemia_context));

	ail_mutex = mutex_create("ail_mutex");
	hw_error_mutex = mutex_create("hw_error_mutex");
	sw_error_mutex = mutex_create("sw_error_mutex");

	CRtc rtc("DEV:rtc");
	
	insulin_pump pump = initialize();

	while (true) {
		write(logpipe, "MAIN\n", strlen("MAIN\n"));

		time = rtc.Read();
		char* time_b = rtc.To_String(time);
		time_b[19] = '\n';
		write(logpipe, time_b, 20);
		if (rtc.Bigger_Or_Equal(time, pump.m_pump_settings.m_basal_profile.m_next_time)) {
			pump.m_pump_settings.m_basal_profile.m_next_time = time;
			do_routine(pump);
			char* time_b = rtc.To_String(pump.m_pump_settings.m_basal_profile.m_next_time);
			time_b[19] = '\n';
			write(logpipe, "Dalsi davka v: ", strlen("Dalsi davka v: "));
			write(logpipe, time_b, 20);
		}
		else {
			if (mutex_lock(ail_mutex)) {
				write(logpipe, "BEZPECNY AIL REZIM\n", strlen("BEZPECNY AIL REZIM\n"));
			}
			else {
				write(logpipe, "AIL task nenasel chybu\n", strlen("AIL task nenasel chybu\n"));
				mutex_unlock(ail_mutex);
			}

			if (mutex_lock(hw_error_mutex)) {
				write(logpipe, "BEZPECNY HW REZIM\n", strlen("BEZPECNY HW REZIM\n"));
			}
			else {
				write(logpipe, "HW task nenasel chybu\n", strlen("HW task nenasel chybu\n"));
				mutex_unlock(hw_error_mutex);
			}

			if (mutex_lock(sw_error_mutex)) {
				write(logpipe, "BEZPECNY SW REZIM\n", strlen("BEZPECNY SW REZIM\n"));
			}
			else {
				write(logpipe, "SW task nenasel chybu\n", strlen("SW task nenasel chybu\n"));
				mutex_unlock(sw_error_mutex);
			}

			sleep(1000, 1000);
		}
	}

	return 0;
}
