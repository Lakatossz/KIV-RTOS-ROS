#pragma once

#include <hal/intdef.h>

enum class NRTC_Command : uint8_t
{
	Nop = 0,

	Read = 1,

	Init = 2,

	Reset = 3,
};

#pragma pack(push, 1)

struct TRTC_Value
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

struct TRTC_Packet_Header
{
	NRTC_Command cmd;
};

struct TRTC_NonParametric_Packet
{
	TRTC_Packet_Header header;
	TRTC_Value date_time;
};

struct TRTC_Datetime_Packet
{
	TRTC_Packet_Header header;
	TRTC_Value date_time;
};

#pragma pack(pop)
