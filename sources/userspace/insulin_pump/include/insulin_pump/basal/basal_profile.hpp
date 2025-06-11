#pragma once

#include "../../utils/logger/logger.hpp"
#include "../../insulin_pump/definitions/definitions.hpp"
#include <rtc.h>

#define DEFAULT_BASAL_PROFILE_TIME_INTERVAL 1

enum basal_unit : uint16_t
{
	Low = 100,
	Normal = 500,
	High = 1000
};

struct basal_profile {
	bool m_basal_set = true;
	uint32_t m_time_interval = DEFAULT_BASAL_PROFILE_TIME_INTERVAL;
	CRtc::time_stamp m_next_time = {};
	basal_unit m_dose_unit = Normal;
};

basal_profile Init();

void Get_Basal_Value(basal_unit unit, float& value);

basal_unit Get_Higher_Value(basal_unit unit);

basal_unit Get_Lower_Value(basal_unit unit);

uint32_t Get_Interval(basal_profile profile);

void Set_Interval(uint32_t time_interval, basal_profile& profile);

basal_unit Get_Dose_Unit(basal_profile profile);

void Set_Dose_Unit(basal_unit unit, basal_profile& profile);

bool Get_Basal_Set(basal_profile profile);

void Change_Basal_Set(basal_profile& profile);

void Add_Interval_Time(basal_profile& profile);

void Reduce_Interval_Time(basal_profile& profile);

