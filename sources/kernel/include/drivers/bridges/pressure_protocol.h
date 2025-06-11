#pragma once

#include <hal/intdef.h>

enum class NPressure_Command : uint8_t
{
	Nop = 0,
	Read = 1,
	Reset = 2,
	Init = 3,
};

#pragma pack(push, 1)

struct TPressure_Value
{
	uint8_t value;
	uint8_t value_decimal;
};

struct TPressure_Packet_Header
{
	NPressure_Command cmd;
};

struct TPressure_NonParametric_Packet
{
	TPressure_Packet_Header header;
	float value;
};

struct TPressure_Value_Packet
{
	TPressure_Packet_Header header;
	TPressure_Value value;
};


#pragma pack(pop)
