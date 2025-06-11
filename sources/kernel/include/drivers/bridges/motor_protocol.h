#pragma once

#include <hal/intdef.h>

enum class NMotor_Command : uint8_t
{
	Nop = 0,
	Push_Forward = 1,
	Push_Backward = 2,
	Reset = 3,
	Read_Status = 4,
	Init = 5,
};

#pragma pack(push, 1)

struct TMotor_Packet_Header
{
	NMotor_Command cmd;
};

struct TMotor_NonParametric_Packet
{
	TMotor_Packet_Header header;
};

struct TMotor_Push_Packet
{
	TMotor_Packet_Header header;
	uint16_t steps;
};

#pragma pack(pop)
