#include "../../include/math/math.hpp"

void pid_integral(const float values[], uint16_t size, float& target) {
	for (int i = 0; i < size; ++i) 
		target += values[i];
}

void pid_derivative(const float values[], uint16_t size, uint32_t index, float& target) {
	if (index >= size)
		target = 0.0f;

	target = values[index] - values[0];
}
