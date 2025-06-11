#pragma once

#include <hal/intdef.h>

enum class NCGM_Command : uint8_t
{
	Nop = 0,
	Reset = 1,
	Init = 2,
	Read_Next = 3,
	Read_Current = 4,
};

#pragma pack(push, 1)

struct TCGM_Packet_Header
{
	NCGM_Command cmd;
};

struct TCGM_NonParametric_Packet
{
	TCGM_Packet_Header header;
	float value;
};

struct TCGM_Value_Packet
{
	TCGM_Packet_Header header;
	float value;
};

#pragma pack(pop)
