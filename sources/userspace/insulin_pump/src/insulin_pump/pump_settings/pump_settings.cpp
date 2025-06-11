#include "../../../include/insulin_pump/pump_settings/pump_settings.hpp"

const char* Settings_State_To_String(settings_state state) {
	switch (state) {
	case Basal:
		return "Podani basalu";
	case BasalValue:
		return "Hodnota basalu";
	case BasalTime:
		return "Casovy interval basalu";
	default:
		return "Hodnota bolusu";
	}
}

pump_setting Initialize_Pump_Settings()
{
	pump_setting settings;
	settings.m_state = settings_state::Basal;
	settings.m_bolus_value = BOLUS_DOSE;
	settings.m_basal_profile = Init();
	settings.m_temp_basal_profile = settings.m_basal_profile;

	return settings;
}

void Reset(pump_setting& settings)
{
	settings.m_state = settings_state::Basal;
	settings.m_bolus_value = BOLUS_DOSE;
	settings.m_basal_profile = Init();
	settings.m_temp_basal_profile = settings.m_basal_profile;
}

settings_state Get_State(pump_setting settings)
{
	return settings.m_state;
}

void Set_Next_State(pump_setting& settings)
{
	if (settings.m_state == Basal) {
		settings.m_state = BasalValue;
	}
	else if (settings.m_state == BasalValue) {
		settings.m_state = BasalTime;
	}
	else if (settings.m_state == BasalTime) {
		settings.m_state = BolusValue;
	}
	else if (settings.m_state == BolusValue) {
		settings.m_state = Action_Required;
	}
	else {
		settings.m_state = Basal;
	}
}

basal_profile Get_Basal_Profile(pump_setting settings)
{
	return settings.m_basal_profile;
}

void Set_Basal_Profile(pump_setting& settings, basal_profile profile)
{
	settings.m_basal_profile = profile;
}

basal_profile Get_Temp_Basal_Profile(pump_setting settings)
{
	return settings.m_temp_basal_profile;
}

void Set_Temp_Basal_Profile(pump_setting& settings, basal_profile profile)
{
	settings.m_temp_basal_profile = profile;
}

float Get_Bolus_Value(pump_setting settings)
{
	return settings.m_bolus_value;
}

void Set_Bolus_Value(pump_setting& settings, const float& value)
{
	settings.m_bolus_value = value;
}

float Get_Temp_Bolus_VaGlue(pump_setting settings)
{
	return settings.m_temp_bolus_value;
}

void Set_Temp_Bolus_Value(pump_setting& settings, const float& value)
{
	settings.m_temp_bolus_value = value;
}
