#include "../../../include/insulin_pump/user_interface/user_interface.hpp"

#include <stdfile.h>

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

#include <process/process_manager.h>

#define LED_SLEEP_TIME 10

class ZeroMate_Interface
{
public:

	ZeroMate_Interface();

	~ZeroMate_Interface() = default;

	void Initialize();

	void Restart();

	bool Test();

	void DisplayMessage(const char* message, uint16_t length);

	float GetUserInput();

	bool GetUserConfirmation();

	void ShowWarning(const char* warning_text, uint16_t length);

	void ShowError(const char* error_text, uint16_t length);

	void ShowCriticalError(const char* critical_error_text, uint16_t length);

	//void RegisterButtonPressCallback(void (*callback)(Pump_Settings& pump_settings, IUser_Interface& ui, bool& bolus_programmed), uint16_t button_id);

private:

	void Blink(uint32_t led_id);

	void ListenForKeyPress();

	CMonitor m_monitor;
	COLED_Display m_oled_display;

	uint32_t m_warning_led_id;
	uint32_t m_error_led_id;
	uint32_t m_critical_error_led_id;

	uint32_t m_button_up_id;
	uint32_t m_button_down_id;
	uint32_t m_button_next_id;
	uint32_t m_button_okay_id;
};
