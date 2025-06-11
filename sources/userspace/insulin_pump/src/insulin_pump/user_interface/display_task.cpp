#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>
#include <oled.h>

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
    COLED_Display oled("DEV:oled");

    oled.Clear();

    oled.Put_String(2, 10, "Display taskoooo.");
    oled.Flip();

    char buf[128];
    bzero(buf, 128);

    uint32_t oledpipe = pipe("oled", 128);
    uint32_t logpipe = pipe("log", 32);

    while (false) {
        write(logpipe, "DISPLAY TASK\n", strlen("DISPLAY TASK\n"));
        wait(oledpipe, 1, Indefinite);
        bzero(buf, 128);
        uint32_t v = read(oledpipe, buf, 16);
        if (v > 0)
        {
            oled.Clear();
            buf[v] = '\0';
            oled.Put_String(2, 10, buf);
            oled.Flip();
        }

        sleep(10, 100);
    }

    return 0;
}
