#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>

#include <drivers/gpio.h>

#include <cgm.h>
#include <pressure.h>
#include <temperature.h>
#include <air_in_line.h>
#include <motor.h>
#include <battery_system.h>
#include <wdt.h>
#include <rtc.h>

#include "../../../../include/insulin_pump/insulin_pump/insulin_pump.hpp"
#include "../../../../include/insulin_pump/pump_settings/pump_settings.hpp"
#include "../../../../include/insulin_pump/insulin_pump/insulin_pump.hpp"

#define HW_TASKS_TICKS 500
#define HW_TASKS_DEADLINE 500

#define MAX_GLYCEMIA 40
#define MIN_GLYCEMIA 5

#define MAX_TEMPERATURE 40
#define MIN_TEMPERATURE 5

#define MAX_PRESSURE 55000
#define MIN_PRESSURE 106000

#define MAX_BATTERY_CHARGE 100000
#define MIN_BATTERY_CHARGE 100 

#define MAX_BATTERY_VOLTAGE 1.1
#define MIN_BATTERY_VOLTAGE 1.6 

#define MAX_BATTERY_CURRENT 2.0
#define MIN_BATTERY_CURRENT 0.9 

uint32_t logpipe;
uint32_t pump_settings_in_pipe;
uint32_t emergency_pipe;
uint32_t hw_error_released;

mutex_t hw_error_mutex;

int main(int argc, char** argv)
{
    logpipe = pipe("log", 32);
    emergency_pipe = pipe("emergency", 1);
    hw_error_released = pipe("hw_error_released", 1);
    pump_settings_in_pipe = pipe("io_task_input", sizeof(pump_setting));
    emergency_pipe = pipe("emergency", 1);

    hw_error_mutex = mutex_create("hw_error_mutex");

    char air_released_c = '0';

    pump_setting settings;
    pump_setting temp_settings;

    CCgm cgm("DEV:cgm");
    CPressure pressure("DEV:press");
    CTemperature temperature("DEV:temp");
    //CAir_In_Line ail("DEV:ail");
    CMotor motor("DEV:motor");
    CBattery_System battery("DEV:battery");
    CWdt wdt("DEV:wdt");
    CRtc rtc("DEV:rtc");

    float value = 0;
    float sum = 0;
    int i = 0;
    uint8_t test_reads = 5;

    while (true) {

        write(logpipe, "HW CONTROL", strlen("HW CONTROL"));

        uint32_t size = read(pump_settings_in_pipe, reinterpret_cast<char*>(&temp_settings), sizeof(pump_setting));

        if (size > 0) {
            write(logpipe, "Zpracovavam", strlen("Zpracovavam"));
            settings = temp_settings;
        }

        if (!cgm.Test()) {
            write(logpipe, "Chyba pri testu cgm", strlen("Chyba pri testu cgm"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }
        else
        {
            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                cgm.Read(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_GLYCEMIA || sum < MIN_GLYCEMIA) {
                write(logpipe, "Nevalidni hodnoty cgm sensoru", strlen("Nevalidni hodnoty cgm sensoru"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }
        }

        if (!pressure.Test()) {
            write(logpipe, "Chyba pri testu senzoru tlaku\n", strlen("Chyba pri testu senzoru tlaku\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }
        else
        {
            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                pressure.Read(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_PRESSURE || sum < MIN_PRESSURE) {
                write(logpipe, "Nevalidni hodnoty tlakoveho sensoru", strlen("Nevalidni hodnoty tlakoveho sensoru"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }
        }

        if (!temperature.Test()) {
            write(logpipe, "Chyba pri testu senzoru teploty\n", strlen("Chyba pri testu senzoru teploty\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }
        else
        {
            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                temperature.Read(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_TEMPERATURE || sum < MIN_TEMPERATURE) {
                write(logpipe, "Nevalidni hodnoty teplotniho sensoru", strlen("Nevalidni hodnoty teplotniho sensoru"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }
        }

        if (!motor.Test()) {
            write(logpipe, "Chyba pri testu motoru\n", strlen("Chyba pri testu motoru\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }
        else {
            write(logpipe, "Otestoval jsem motor\n", strlen("Otestoval jsem motor\n"));
        }

        if (!battery.Test()) {
            write(logpipe, "Chyba pri testu baterie\n", strlen("Chyba pri testu baterie\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }
        else
        {
            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                battery.Get_Charge(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_BATTERY_CHARGE || sum < MIN_BATTERY_CHARGE) {
                write(logpipe, "Nevalidni hodnoty urovne nabiti baterie", strlen("Nevalidni hodnoty urovne nabiti baterie"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }

            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                battery.Get_Voltage(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_BATTERY_VOLTAGE || sum < MIN_BATTERY_VOLTAGE) {
                write(logpipe, "Nevalidni hodnoty napeti baterie", strlen("Nevalidni hodnoty napeti baterie"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }

            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                battery.Get_Current(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_BATTERY_CURRENT || sum < MIN_BATTERY_CURRENT) {
                write(logpipe, "Nevalidni hodnoty proudu baterie", strlen("Nevalidni hodnoty proudu baterie"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }

            sum = 0;
            for (i = 0; i < test_reads; ++i) {
                battery.Get_Temperature(value);
                sum += value;
            }

            sum /= test_reads;

            if (sum > MAX_TEMPERATURE || sum < MIN_TEMPERATURE) {
                write(logpipe, "Nevalidni hodnoty teploty baterie", strlen("Nevalidni hodnoty teploty baterie"));
                // Poslu signal do io tasku, aby uzivatel oznamil 
                write(emergency_pipe, "1", 1);
            }
        }

        if (!wdt.Test()) {
            write(logpipe, "Chyba pri testu wdt\n", strlen("Chyba pri testu wdt\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }

        if (!rtc.Test()) {
            write(logpipe, "Chyba pri testu rtc\n", strlen("Chyba pri testu rtc\n"));
            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);
        }


        sleep(HW_TASKS_TICKS, HW_TASKS_DEADLINE);
    }

    return 0;
}
