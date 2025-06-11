#include "../../../include/insulin_pump/insulin_pump/insulin_pump.hpp"
#include <monitor.h>

// Explicitní deklarace pro potlačení built-in funkcí
void* memcpy(void* dest, const void* src, size_t n) {
	char* d = static_cast<char*>(dest);
	const char* s = static_cast<const char*>(src);
	while (n--) *d++ = *s++;
	return dest;
}

insulin_pump initialize()
{
	insulin_pump pump;

	pump.m_logpipe = pipe("log", 128);
	//pump.m_cgm = CCgm("DEV:cgm");
	//pump.m_motor = CMotor("DEV:motor");
	//pump.m_pid_regulator = Initialize_Pid_Regulator();
	//pump.m_pump_settings = Initialize_Pump_Settings();

	return pump;
}

int do_routine(insulin_pump & pump)
{
	Read_Current_Glycemia(pump);

	Get_Current_Basal_Dose(pump);

	Get_Current_Dose(pump);

	Give_Dose(pump);

	//Analyze_Given_Dose(pump);

	return 1;
}

void Read_Current_Glycemia(insulin_pump& pump)
{
	Debug(pump.m_logpipe, READ_GLYCEMIA_CONFIRMATION, strlen(READ_GLYCEMIA_CONFIRMATION));

	pump.m_cgm.Read(pump.m_current_glycemia);

	pump.m_current_glycemia = 1.0f;
	pump.m_hypoglycemia_treshold = 10.0f;

	if (Glycemia_Reached_Treshold(pump)) {
		Error(pump.m_logpipe, HYPOGLYCEMIA_NOTIFICATION, strlen(HYPOGLYCEMIA_NOTIFICATION));
		return;
	} else
		Debug(pump.m_logpipe, "Nebo ne", strlen("Nebo ne"));

	//Push_Last_Measured(pump.m_pid_regulator, pump.m_current_glycemia);
}

void Get_Current_Basal_Dose(insulin_pump& pump)
{
	//Predicate_Next_Insuline_Basal_Rate(pump.m_pid_regulator, Get_Basal_Profile(pump.m_pump_settings), pump.m_basal_dose);

	//char buffer[10] = {};
	//ftoa(pump.m_basal_dose, buffer, 10);

	Debug(pump.m_logpipe, READ_BASAL_DOSE_CONFIRMATION, strlen(READ_BASAL_DOSE_CONFIRMATION));
	//Debug(pump.m_logpipe, buffer, strlen(buffer));
}

void Get_Current_Dose(insulin_pump& pump)
{
	if (pump.m_bolus_programmed) {
		Debug(pump.m_logpipe, "bolus naprogramovany", strlen("bolus naprogramovany"));
		//Get_Basal_Value(pump.m_pump_settings.m_basal_profile.m_dose_unit, basal_value);
		//pump.m_total_dose = pump.m_pump_settings.m_basal_profile.m_dose_unit + pump.m_pump_settings.m_bolus_value;
		pump.m_bolus_programmed = false;
	}
	else {
		Debug(pump.m_logpipe, "bolus neni naprogramovany", strlen("bolus neni naprogramovany"));
		//pump.m_total_dose = pump.m_pump_settings.m_basal_profile.m_dose_unit;
		//Get_Basal_Value(pump.m_pump_settings.m_basal_profile.m_dose_unit, pump.m_total_dose);
	}

	pump.m_dose_to_give = true;

	char basal_buffer[10] = {};
	//ftoa(pump.m_basal_dose, basal_buffer, 10);
	// 
	//Debug(pump.m_logpipe, basal_buffer, strlen(basal_buffer));

	char total_buffer[10] = {};

	//ftoa(pump.m_basal_dose, total_buffer, 10);

	Debug(pump.m_logpipe, READ_TOTAL_DOSE_CONFIRMATION, strlen(READ_TOTAL_DOSE_CONFIRMATION));
	//Debug(pump.m_logpipe, total_buffer, strlen(total_buffer));
}

void Give_Dose(insulin_pump& pump)
{
	if (pump.m_dose_to_give) {
		//pump.m_motor.Move_Forward(static_cast<uint16_t>(pump.m_total_dose * 100));
		pump.m_motor.Move_Forward(10);
		pump.m_dose_to_give = false;
		pump.m_pump_settings.m_basal_profile.m_next_time.minute += pump.m_pump_settings.m_basal_profile.m_time_interval;
		pump.m_pump_settings.m_basal_profile.m_next_time.minute %= 60;
		Debug(pump.m_logpipe, GIVING_NECESSARY_DOSE, strlen(GIVING_NECESSARY_DOSE));
	} else
		Debug(pump.m_logpipe, "Nebudu davkovat", strlen("Nebudu davkovat"));
}

void Analyze_Given_Dose(insulin_pump& pump)
{
	Debug(pump.m_logpipe, "Analyzuji reakci pacienta na podanou davku", strlen("Analyzuji reakci pacienta na podanou davku"));

	for (int i = 0; i < 10; ++i) {
		Read_Current_Glycemia(pump);
	}
}

bool Is_Bolus_Programmed(insulin_pump& pump)
{
	return pump.m_bolus_programmed;
}

bool Glycemia_Reached_Treshold(insulin_pump& pump)
{
	return pump.m_current_glycemia < pump.m_hypoglycemia_treshold;
}

void Stop_Dosing(insulin_pump& pump)
{
	pump.m_bolus_dose = 0.0f;
	pump.m_bolus_programmed = false;
	pump.m_basal_dose = 0.0f;
	pump.m_basal_perimted = false;
	pump.m_bolus_permited = false;
}
