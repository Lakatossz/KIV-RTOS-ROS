#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <monitor.h>
#include <drivers/gpio.h>
#include <temperature.h>
#include <cgm.h>

#include "../../../../include/insulin_pump/insulin_pump/insulin_pump.hpp"
#include "../../../../include/insulin_pump/pump_settings/pump_settings.hpp"
#include "../../../../include/insulin_pump/insulin_pump/insulin_pump.hpp"

#define SW_TASKS_TICKS 1000
#define SW_TASKS_DEADLINE 1000

uint32_t logpipe;
uint32_t io_sw_task_output;
uint32_t hw_error_released;
uint32_t emergency_pipe;
uint32_t glycemia_context_pipe;
uint32_t sw_error_mutex;

// Explicitní deklarace pro potlaèení built-in funkcí
extern "C" void* memcpy(void* dest, const void* src, size_t n) {
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    while (n--) *d++ = *s++;
    return dest;
}

bool sw_control_routine(glycemia_context context) {

    float diff = 0.0f;

    uint32_t hypoglycemia_counter = 0;
    uint32_t hyperglycemia_counter = 0;

    for (int i = 0; i < GLYCEMIA_HISTORY_SIZE; ++i) {
        if (context.m_glycemia_history[i] > context.m_max_glycemia 
            || context.m_glycemia_history[i] < context.m_min_glycemia) {
            return false;
        }

        if (context.m_glycemia_history[i] > context.m_hyperglycemia) {
            hyperglycemia_counter++;
            if (hyperglycemia_counter > MAX_HYPERGLYCEMIA_COUNTER) {
                return false;
            }
        }
        
        if (context.m_glycemia_history[i] < context.m_hypoglycemia) {
            hypoglycemia_counter++;
            if (hypoglycemia_counter > MAX_HYPOGLYCEMIA_COUNTER) {
                return false;
            }
        }

        if (context.m_glycemia_history[i] != 0.0f) {
            diff += context.referenced_value - context.m_glycemia_history[i];
        }
    }

    if (diff > MAX_GLYCEMIA_DIF || (-diff) > MAX_GLYCEMIA_DIF) {
        return false;
    }
    
    for (int i = 0; i < INSULIN_HISTORY_SIZE; ++i) {
        if (context.m_insulin_history[i] > context.m_max_insulin 
            || context.m_insulin_history[i] < context.m_min_insulin) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    logpipe = pipe("log", 128);
    io_sw_task_output = pipe("io_sw_pipe", sizeof(pump_setting));
    hw_error_released = pipe("sw_error_released", 1);
    glycemia_context_pipe = pipe("glycemia_context", sizeof(glycemia_context));

    glycemia_context m_context;
    glycemia_context m_temp_context;

    sw_error_mutex = mutex_create("sw_error_mutex");

    char hw_error_released_c = '0';

    while (true) {

        write(logpipe, "SW CONTROL\n", strlen("SW CONTROL\n"));

        uint32_t size = read(glycemia_context_pipe, reinterpret_cast<char*>(&m_temp_context), sizeof(glycemia_context));

        if (size > 0) {
            m_context = m_temp_context;
        }

        if (!sw_control_routine(m_context)) {
            write(logpipe, "Chyba SW validace\n", strlen("Chyba SW validace\n"));

            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);

            write(logpipe, "Poslal jsem EMERGENCY z SW\n", strlen("Poslal jsem EMERGENCY z SW\n"));

            // Uzamknu mutex a odmeknu ho, az uzivatel uvolni bublinu
            mutex_lock(sw_error_mutex);

            write(logpipe, "Jsem za zamkem\n", strlen("Jsem za zamkem\n"));

            wait(hw_error_released, 1, Indefinite);

            write(logpipe, "Dockal jsem se v SW\n", strlen("Dockal jsem se v SW\n"));

            read(hw_error_released, &hw_error_released_c, 1);

            if (hw_error_released_c == '1') {
                write(logpipe, "Odstranil jsem SW chybu\n", strlen("Odstranil jsem  SW chybu\n"));
            }
        }

        sleep(SW_TASKS_TICKS, SW_TASKS_DEADLINE);
    }

    return 0;
}
