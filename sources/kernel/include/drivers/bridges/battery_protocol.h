#pragma once

#include <hal/intdef.h>

enum class NBattery_Command : uint8_t
{
	Nop = 0,
	// Pouziju na cteni informaci z baterie
	Read_Charge = 1,
	Read_Voltage = 2,
	Read_Current = 3,
	Read_Temperature = 4,
	Read_Errors = 5,
	Read_Info = 6,
	// Pouziju na zmenu nastaveni baterie
	Reset = 7,
};

#pragma pack(push, 1)

struct TBattery_Value
{
	uint8_t value;
};

struct TBattery_Packet_Header
{
	NBattery_Command cmd;
};

struct TBattery_NonParametric_Packet
{
	TBattery_Packet_Header header;
	float value;
};
struct TBattery_Info_Packet
{
	TBattery_Packet_Header header;
	TBattery_Value charge;
	TBattery_Value voltage;
	TBattery_Value current;
	TBattery_Value temperature;
	TBattery_Value errors;
	TBattery_Value info;
};

#pragma pack(pop)

