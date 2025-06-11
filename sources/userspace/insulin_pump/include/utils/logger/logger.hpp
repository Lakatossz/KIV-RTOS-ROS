// ---------------------------------------------------------------------------------------------------------------------
/// \file logger.hpp
/// \date 19. 03. 2023
/// \author Jaroslav Rosa (rosajaro1352@gmail.com)
///
/// \brief This file defines Logger for Insulin Pump
// ---------------------------------------------------------------------------------------------------------------------


#pragma once

// STL imports (excluded from Doxygen)
/// \cond
//#include <iostream>
//#include <format>
//#include <chrono>
//#include "../../../stdlib/include/stdstring.h"
#include <stdstring.h>
#include <stdfile.h>
#include "monitor.h"
#include <rtc.h>
/// \endcond

using namespace std;

// -----------------------------------------------------------------------------------------------------------------
/// \class IIPLogger
/// \brief 
///
/// 
// -----------------------------------------------------------------------------------------------------------------
enum class NLogging_Level : uint8_t
{
	Debug = 0,
	Info = 1,
	Warning = 2,
	Error = 3,
	Critical = 4
};

void Set_Logger();

void Debug(uint32_t m_logpipe, const char* string, uint16_t length);

void Info(uint32_t m_logpipe, const char* string, uint16_t length);

void Warning(uint32_t m_logpipe, const char* string, uint16_t length);

void Error(uint32_t m_logpipe, const char* string, uint16_t length);


