#include "../../../include/insulin_pump/pid_regulator/pid_regulator.hpp"

extern "C" void* memset(void* ptr, int value, uint32_t num) {
	uint8_t* p = (uint8_t*)ptr;
	for (uint32_t i = 0; i < num; ++i) p[i] = (uint8_t)value;
	return ptr;
}

pid_regulator Initialize_Pid_Regulator()
{
	pid_regulator regulator;
	regulator.m_referenced_value = 6.6f;
	regulator.m_measured_size = 5;
	regulator.m_current_measured = 0;
	regulator.m_k_p = 0.1f;
	regulator.m_k_i = 0.1f;
	regulator.m_k_d = 0.1f;
	regulator.m_max_output = 1.0f;
	for (int i = 0; i < ARRAY_SIZE; ++i){
		regulator.m_measured_values[i] = 0;
		regulator.m_error_values[i] = 0;
	}
	regulator.m_integral_sum = 0.0f;
	
	return regulator;
}

void Push_Last_Measured(pid_regulator& pid_r, float last_measured)
{
	//pid_r.m_current_measured = (pid_r.m_current_measured + 1) % pid_r.m_measured_size;

	/*if (pid_r.m_current_measured < ARRAY_SIZE) {
		pid_r.m_measured_values[pid_r.m_current_measured] = last_measured;
		pid_r.m_error_values[pid_r.m_current_measured] = pid_r.m_referenced_value - last_measured;
		pid_r.m_integral_sum += pid_r.m_error_values[pid_r.m_current_measured];
	}*/
	//clamp(pid_r.m_integral_sum, -pid_r.m_max_output, pid_r.m_max_output);
}

void Predicate_Next_Insuline_Basal_Rate(pid_regulator pid_r, basal_profile basal_profile, float& value)
{
	if (basal_profile.m_basal_set) {
		return;
	}

	float proportional = 0.0f, integral = 0.0f, derivative = 0.0f, dose_unit = 0.0f;

	proportional = pid_r.m_error_values[pid_r.m_current_measured];
	//Get_Proportional(pid_r, proportional);
	if (proportional < MIN_PROPORTIONAL || proportional > MAX_PROPORTIONAL) {
		return;
	}

	pid_integral(pid_r.m_measured_values, ARRAY_SIZE, integral);
	//Get_Integral(pid_r, integral);
	if (integral < MIN_INTEGRAL || integral > MAX_INTEGRAL) {
		return;
	}

	pid_derivative(pid_r.m_measured_values, ARRAY_SIZE, pid_r.m_current_measured, derivative);
	//Get_Derivative(pid_r, derivative);
	if (derivative < MIN_DERIVATIVE || derivative > MAX_DERIVATIVE) {
		return;
	}

	dose_unit = basal_profile.m_dose_unit;
	//dose_unit = Get_Dose_Unit(basal_profile);
	if (dose_unit < 0.0f) {
		return;
	}

	float ibr = -pid_r.m_k_p * proportional
		- pid_r.m_k_i * integral
		- pid_r.m_k_d * derivative
		+ (float)(dose_unit); // ibr0

	value = ibr;
}

void Get_Proportional(pid_regulator& pid_r, float& value)
{
	value = pid_r.m_error_values[pid_r.m_current_measured];
}

void Get_Integral(pid_regulator& pid_r, float& value)
{
	pid_integral(pid_r.m_measured_values, ARRAY_SIZE, value);
}

void Get_Derivative(pid_regulator& pid_r, float& value)
{
	pid_derivative(pid_r.m_measured_values, ARRAY_SIZE, pid_r.m_current_measured, value);
}

void clamp(float& value, float minval, float maxval) {
	if (value < minval) {
		value = minval;
	}
	else if (value > maxval) {
		value = maxval;
	}
}

