#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>

#include <oled.h>
#include <cgm.h>
#include <motor.h>
#include <air_in_line.h>
#include <battery_system.h>
#include <pressure.h>
#include <temperature.h>
#include <wdt.h>
#include <rtc.h>
#include <monitor.h>

#include <drivers/bridges/uart_defs.h>
#include <drivers/gpio.h>

/**
 * Displejovy task
 * 
 * Zobrazuje hlasky na OLED displeji, a pokud prijde udalost od jinych tasku, zobrazi neco relevantniho k nim
 **/

const char* messages[] = {
	"I blink, therefore I am.",
	"I see dead pixels.",
	"One CPU rules them all.",
	"My favourite sport is ARM wrestling",
	"Old MacDonald had a farm, EIGRP",
};

int main(int argc, char** argv)
{
	COLED_Display disp("DEV:oled");
	disp.Clear(false);
	disp.Put_String(10, 10, "KIV-RTOS init...");
	disp.Flip();

	CMonitor monitor("DEV:monitor");

	monitor.Clear();
	monitor.Put("1\n", strlen("1\n"));

	CCgm cgm("DEV:cgm");
	CMotor motor("DEV:motor");
	//CAir_In_Line ail("DEV:ail");
	CBattery_System battery("DEV:battery");
	CTemperature temperature("DEV:temp");
	CRtc rtc("DEV:rtc");
	CPressure pressure("DEV:press");
	CWdt wdt("DEV:wdt");

	sleep(0x800, 0x800);

	uint32_t trng_file = open("DEV:trng", NFile_Open_Mode::Read_Only);
	uint32_t num = 0;

	//uint32_t current_cgm = cgm.Read();
	//uint32_t current_ail = ail.Read();
	//uint32_t current_temp = temperature.Read();
	//uint32_t current_time = rtc.Read();
	//uint32_t current_press = pressure.Read();
	//uint32_t current_charge = battery.Get_Charge();

	//motor.Move_Forward(5);

	/*while (true)
	{
		// ziskame si nahodne cislo a vybereme podle toho zpravu
		read(trng_file, reinterpret_cast<char*>(&num), sizeof(num));
		const char* msg = messages[num % (sizeof(messages) / sizeof(const char*))];

		current_cgm = cgm.Read();

		//motor.Move_Forward(5);

		//current_temp = temperature.Read();

		//monitor.Put(reinterpret_cast<char*>(&current_cgm), 1);
		//monitor.Put("\n", 1);

		//disp.Clear(false);
		//disp.Put_String(0, 0, msg);
		//disp.Flip();

		sleep(0x4000, 0x800); // TODO: z tohohle bude casem cekani na podminkove promenne (na eventu) s timeoutem
	}*/

    return 0;
}
