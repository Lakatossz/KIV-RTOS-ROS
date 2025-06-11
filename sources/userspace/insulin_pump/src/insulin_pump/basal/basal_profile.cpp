#include "../../../include/insulin_pump/basal/basal_profile.hpp"

basal_profile Init()
{
	basal_profile profile;
	profile.m_basal_set = true;
	profile.m_dose_unit = Normal;
	profile.m_time_interval = DEFAULT_BASAL_PROFILE_TIME_INTERVAL;
	return profile;
}

uint32_t Get_Interval(basal_profile profile)
{
	return profile.m_time_interval;
}

void Set_Interval(uint32_t time_interval, basal_profile& profile)
{
	profile.m_time_interval = time_interval;
	char buffer[10] = {};
	itoa(time_interval, buffer, 10);
}

void Get_Basal_Value(basal_unit unit, float& value)
{
	value = static_cast<float>(static_cast<uint32_t>(unit)) / 100.0f;
}

basal_unit Get_Higher_Value(basal_unit unit)
{
	if (unit == basal_unit::Low)
		return basal_unit::Normal;
	else if (unit == basal_unit::Normal)
		return basal_unit::High;
	else
		return basal_unit::Low;
}

basal_unit Get_Lower_Value(basal_unit unit)
{
	if (unit == basal_unit::Low)
		return basal_unit::High;
	else if (unit == basal_unit::Normal)
		return basal_unit::Low;
	else
		return basal_unit::Normal;
}

basal_unit Get_Dose_Unit(basal_profile profile)
{
	return profile.m_dose_unit;
}

void Set_Dose_Unit(basal_unit unit, basal_profile& profile)
{
	profile.m_dose_unit = unit;
	float basal_value = 0.0f;
	Get_Basal_Value(unit, basal_value);
}

bool Get_Basal_Set(basal_profile profile)
{
	return profile.m_basal_set;
}

void Change_Basal_Set(basal_profile& profile)
{
	profile.m_basal_set = !profile.m_basal_set;
}

void Add_Interval_Time(basal_profile& profile)
{
	if ((profile.m_time_interval + BASAL_TIME_STEP) <= MAX_BASAL_TIME) {
		profile.m_time_interval += BASAL_TIME_STEP;
	}
}

void Reduce_Interval_Time(basal_profile& profile)
{
	if ((profile.m_time_interval - BASAL_TIME_STEP) >= 0) {
		profile.m_time_interval -= BASAL_TIME_STEP;
	}
}
