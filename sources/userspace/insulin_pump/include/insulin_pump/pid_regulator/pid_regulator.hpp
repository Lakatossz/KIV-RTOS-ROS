#pragma once

#include <stdstring.h>

#include "../../utils/logger/logger.hpp"
#include "../basal/basal_profile.hpp"
#include "../../math/math.hpp"

#define ARRAY_SIZE 15

#define MIN_PROPORTIONAL 0.0f
#define MAX_PROPORTIONAL 1.0f

#define MIN_INTEGRAL 0.0f
#define MAX_INTEGRAL 1.0f

#define MIN_DERIVATIVE 0.0f
#define MAX_DERIVATIVE 1.0f

extern "C" void* memset(void* ptr, int value, uint32_t num);

struct pid_regulator {
	float m_referenced_value = 6.6f;
	uint32_t m_measured_size = 5;
	uint32_t m_current_measured = 0;
	float m_k_p = 0.1f;
	float m_k_i = 0.1f;
	float m_k_d = 0.1f;
	float m_max_output = 1.0f;
	float m_measured_values[ARRAY_SIZE] = { 0 };
	float m_error_values[ARRAY_SIZE] = { 0 };
	float m_integral_sum = 0.0f;
};

pid_regulator Initialize_Pid_Regulator();

void Push_Last_Measured(pid_regulator& pid_r, float last_measured);

void Predicate_Next_Insuline_Basal_Rate(pid_regulator pid_r, basal_profile basal_profile, float& value);

void Get_Proportional(pid_regulator& pid_r, float& value);

void Get_Integral(pid_regulator& pid_r, float& value);

void Get_Derivative(pid_regulator& pid_r, float& value);

void clamp(float& value, float minval, float maxval);
