#pragma once

#include <stdfile.h>
#include <stdmutex.h>

void pid_integral(const float values[], uint16_t size, float& target);

void pid_derivative(const float values[], uint16_t size, uint32_t index, float& target);
