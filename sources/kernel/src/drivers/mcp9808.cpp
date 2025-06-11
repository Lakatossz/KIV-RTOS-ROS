#include <drivers/mcp9808.h>
#include <memory/kernel_heap.h>
#include <stdstring.h>
#include <drivers/monitor.h>

#include <drivers/bridges/temperature_protocol.h>

CMcp9808 sMcp9808(sI2C1);

CMcp9808::CMcp9808(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{
}
bool CMcp9808::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CMcp9808::Send_Command(Mcp9808_Sensor_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(Mcp9808_Slave_Address);

	ta << Mcp9808_Sensor_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CMcp9808::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NTemperature_Command cmd = static_cast<NTemperature_Command>(input[0]);

	switch (cmd)
	{
	case NTemperature_Command::Nop:
		break;

	case NTemperature_Command::Init:
	{
		auto& ta = mI2C.Begin_Transaction(Mcp9808_Slave_Address);

		ta << Mcp9808_Sensor_Cmd::Command_Start << Mcp9808_Sensor_Cmd::Write_Init;

		mI2C.End_Transaction(ta);
		break;
	}
	case NTemperature_Command::Reset:
	{
		auto& ta = mI2C.Begin_Transaction(Mcp9808_Slave_Address);

		ta << Mcp9808_Sensor_Cmd::Command_Start << Mcp9808_Sensor_Cmd::Write_Reset;

		mI2C.End_Transaction(ta);
		break;
	}
	}
}

void CMcp9808::Close()
{
	if (!mOpened)
		return;

	mI2C.Close();

	mOpened = false;
}

bool CMcp9808::Is_Opened() const
{
	return mOpened;
}

uint32_t CMcp9808::Read(char*& buffer)
{
	TTemperature_Value_Packet* cmd = reinterpret_cast<TTemperature_Value_Packet*>(buffer);

	uint8_t bytes[4] = { 0 };

	// 1. Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta = mI2C.Begin_Transaction(Mcp9808_Slave_Address);

	// 2. Zapsání adresy registru (Read_Charge)
	ta << Mcp9808_Sensor_Cmd::Command_Start << Mcp9808_Sensor_Cmd::Read_Value;

	// 3. Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta);

	// 4. Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& taRead = mI2C.Begin_Transaction(Mcp9808_Slave_Address | 1);  // Pøidání R bit (Read)

	// 6. Ukonèení transakce pro ètení
	mI2C.End_Transaction(taRead, true, true, 4);

	// 5. Ètení dat pøímo po pøepnutí na režim ètení
	taRead >> bytes[0] >> bytes[1] >> bytes[2] >> bytes[3];

	memcpy(&cmd->value, bytes, sizeof(float));

	return sizeof(cmd->value);
}

bool CMcp9808::Test_Peripheral()
{
	return true;
}
