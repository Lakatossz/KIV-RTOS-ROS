#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <drivers/gpio.h>
#include <air_in_line.h>

uint32_t logpipe;
uint32_t emergency_pipe;
uint32_t air_in_line;
uint32_t air_released;

bool bubble_found = false;

mutex_t ail_mutex;

static void fputs(uint32_t file, const char* string)
{
    write(file, string, strlen(string));
}

int main(int argc, char** argv)
{
    logpipe = pipe("log", 128);
    emergency_pipe = pipe("emergency", 1);
    air_released = pipe("air_released", 1);

    write(logpipe, "AIR IN LINE TASK\n", strlen("AIR IN LINE TASK\n"));

    CAir_In_Line air_in_line = CAir_In_Line();

    ail_mutex = mutex_create("ail_mutex");

    char air_released_c = '0';

    while (true) {
        bubble_found = air_in_line.Wait_For_Air();

        if (air_in_line.Wait_For_Air()) {

            // Zaloguje udalost
            write(logpipe, "AIR IN LINE\n", strlen("AIR IN LINE\n"));

            // Poslu signal do io tasku, aby uzivatel oznamil 
            write(emergency_pipe, "1", 1);

            write(logpipe, "Poslal jsem EMERGENCY\n", strlen("Poslal jsem EMERGENCY\n"));

            // Uzamknu mutex a odmeknu ho, az uzivatel uvolni bublinu
            mutex_lock(ail_mutex);

            write(logpipe, "Jsem za zamkem\n", strlen("Jsem za zamkem\n"));

            //wait(air_released, 1, 1);

            //write(logpipe, "Dockal jsem se\n", strlen("Dockal jsem se\n"));

            //read(air_released, &air_released_c, 1);

            //if (air_released_c == '1') {
            //    write(logpipe, "Odstranil jsem vzduch\n", strlen("Odstranil jsem vzduch\n"));
           // }
        }
    }

    return 0;
}
