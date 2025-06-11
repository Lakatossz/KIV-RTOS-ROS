#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <monitor.h>

/**
 * Logger task
 *
 * Prijima vsechny udalosti od ostatnich tasku a oznamuje je skrz UART hostiteli
 **/

static void fputs(uint32_t file, const char* string)
{
    write(file, string, strlen(string));
}

int main(int argc, char** argv)
{
    uint32_t monitor_file = open("DEV:monitor/0", NFile_Open_Mode::Read_Write);

    ioctl(monitor_file, NIOCtl_Operation::Enable_Event_Detection, nullptr);

    fputs(monitor_file, "Monitor task starting!!\n");

    char buf[128];
    char tickbuf[16];
    bzero(buf, 16);
    bzero(tickbuf, 16);

    uint32_t last_tick = 0;

    uint32_t logpipe = pipe("log", 128);

    while (true)
    {
        wait(logpipe, 1, Indefinite);

        uint32_t v = read(logpipe, buf, 128);
        if (v > 0)
        {
            buf[v] = '\0';
            fputs(monitor_file, "[ ");
            uint32_t tick = get_tick_count();
            itoa(tick, tickbuf, 10);
            fputs(monitor_file, tickbuf);
            fputs(monitor_file, "]: ");
            fputs(monitor_file, buf);
        }

        sleep(10, 100);
    }

    return 0;
}
