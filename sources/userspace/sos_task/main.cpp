#include <stdstring.h>
#include <stdfile.h>
#include <stdmutex.h>

#include <drivers/gpio.h>

#include <air_in_line.h>
#include <wdt.h>
#include <monitor.h>
#include <motor.h>
#include <cgm.h>
#include <battery_system.h>
#include <rtc.h>
#include <pressure.h>
#include <temperature.h>

/**
 * SOS blinker task
 * 
 * Ceka na stisk tlacitka, po stisku vyblika LEDkou "SOS" signal
 **/

int main(int argc, char** argv)
{
	//Insulin_Pump insulin_pump = Insulin_Pump();

	//insulin_pump.Initialize();

	//return insulin_pump.Run();

	//Insulin_Pump insulin_pump();

	//CMonitor monitor("DEV:monitor");
	//monitor.Clear();

	//CTemperature temp("DEV:temp");

	//CAir_In_Line ail("DEV:ail");
	//CWdt wdt("DEV:wdt");

	//CMotor motor("DEV:motor");

	//CCgm cgm("DEV:cgm");

	//CBattery_System battery("DEV:battery");
	//CRtc rtc("DEV:rtc");
	//CPressure pressure("DEV:press");

	//while (true)
	//{
	//float current_cgm = 5.0f;
	//cgm.Read(current_cgm);

		//uint32_t current_time = rtc.Read();
		//uint32_t current_press = pressure.Read();
		//uint32_t current_charge = battery.Get_Charge();

		//uint32_t temperature = temp.Read();
		//motor.Move_Forward(10);
		//motor.Move_Backward(5);
		//monitor.Put("Pred\n", strlen("Pred\n"));
		//wdt.Barked();
	//}

    return 0;
}
