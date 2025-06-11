#pragma once

#include <hal/intdef.h>

enum class NTemperature_Command : uint8_t
{
	Nop = 0,
	Read = 1,
	Reset = 2,
	Init = 3,
};

#pragma pack(push, 1)

struct TTemperature_Value
{
	uint8_t value;
	uint8_t value_decimal;
};

struct TTemperature_Packet_Header
{
	NTemperature_Command cmd;
};

struct TTemperature_NonParametric_Packet
{
	TTemperature_Packet_Header header;
	float value;
};

struct TTemperature_Value_Packet
{
	TTemperature_Packet_Header header;
	TTemperature_Value value;
};


#pragma pack(pop)
