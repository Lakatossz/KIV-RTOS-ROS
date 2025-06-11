#include "../../../include/insulin_pump/user_interface/zero_mate_user_interface.hpp"

ZeroMate_Interface::ZeroMate_Interface()
	: m_monitor{ CMonitor("DEV:monitor") }
	, m_oled_display{ COLED_Display("DEV:oled") }
	, m_warning_led_id{ open("DEV:gpio/5", NFile_Open_Mode::Write_Only) }
	, m_error_led_id{ open("DEV:gpio/6", NFile_Open_Mode::Write_Only) }
	, m_critical_error_led_id{ open("DEV:gpio/25", NFile_Open_Mode::Write_Only) }
	, m_button_up_id{ open("DEV:gpio/16", NFile_Open_Mode::Read_Only) }
	, m_button_down_id{ open("DEV:gpio/17", NFile_Open_Mode::Read_Only) }
	, m_button_next_id{ open("DEV:gpio/22", NFile_Open_Mode::Read_Only) }
	, m_button_okay_id{ open("DEV:gpio/23", NFile_Open_Mode::Read_Only) }
{

}

void ZeroMate_Interface::Initialize()
{
	/*NGPIO_Interrupt_Type irtype = NGPIO_Interrupt_Type::Rising_Edge;
	ioctl(m_button_up_id, NIOCtl_Operation::Enable_Event_Detection, &irtype);
	ioctl(m_button_down_id, NIOCtl_Operation::Enable_Event_Detection, &irtype);
	ioctl(m_button_next_id, NIOCtl_Operation::Enable_Event_Detection, &irtype);
	ioctl(m_button_okay_id, NIOCtl_Operation::Enable_Event_Detection, &irtype);*/
}

void ZeroMate_Interface::Restart()
{
	m_monitor.Clear();
	m_oled_display.Clear();

	close(m_warning_led_id);
	close(m_error_led_id);
	close(m_critical_error_led_id);
	close(m_button_up_id);
	close(m_button_down_id);
	close(m_button_next_id);
	close(m_button_okay_id);
	
	m_monitor = CMonitor("DEV:monitor");
	m_oled_display = COLED_Display("DEV:oled");
	m_warning_led_id = open("DEV:gpio/5", NFile_Open_Mode::Write_Only);
	m_error_led_id = open("DEV:gpio/6", NFile_Open_Mode::Write_Only);
	m_critical_error_led_id = open("DEV:gpio/25", NFile_Open_Mode::Write_Only);
	m_button_up_id = open("DEV:gpio/16", NFile_Open_Mode::Read_Only);
	m_button_down_id = open("DEV:gpio/17", NFile_Open_Mode::Read_Only);
	m_button_next_id = open("DEV:gpio/22", NFile_Open_Mode::Read_Only);
	m_button_okay_id = open("DEV:gpio/23", NFile_Open_Mode::Read_Only);
}

bool ZeroMate_Interface::Test()
{
	return m_monitor.Test() && m_oled_display.Test();
}

void ZeroMate_Interface::DisplayMessage(const char* message, uint16_t length)
{
	if (m_monitor.Is_Opened()) {
		m_monitor.Put(message, length);
	}


	if (m_oled_display.Is_Opened()) {
		m_oled_display.Put_String(10, 10, message);
	}
}

float ZeroMate_Interface::GetUserInput()
{
	float input = 0.0f;
	return input;
}

bool ZeroMate_Interface::GetUserConfirmation()
{
	char response;
	return (response == 'y' || response == 'Y');
}

void ZeroMate_Interface::ShowWarning(const char* warning_text, uint16_t length)
{
	Blink(m_warning_led_id);
	if (m_monitor.Is_Opened()) {
		m_monitor.Put(warning_text, length);
	}
}

void ZeroMate_Interface::ShowError(const char* error_text, uint16_t length)
{
	Blink(m_error_led_id);
	if (m_monitor.Is_Opened()) {
		m_monitor.Put(error_text, length);
	}
}

void ZeroMate_Interface::ShowCriticalError(const char* critical_error_text, uint16_t length)
{	
	Blink(m_critical_error_led_id);
	if (m_monitor.Is_Opened()) {
		m_monitor.Put(critical_error_text, length);
	}

	if (m_oled_display.Is_Opened()) {
		m_oled_display.Put_String(10, 10, critical_error_text);
	}
}

//void ZeroMate_Interface::RegisterButtonPressCallback(void (*callback)(Pump_Settings& pump_settings, IUser_Interface& ui, bool& bolus_programmed), uint16_t button_id) 
//{

//}

void ZeroMate_Interface::Blink(uint32_t led_id)
{
	write(led_id, "1", 1);
	sleep(LED_SLEEP_TIME);
	write(led_id, "0", 1);
}

void ZeroMate_Interface::ListenForKeyPress() {

}
