#include <drivers/cgm_sensor.h>
#include <memory/kernel_heap.h>
#include <stdstring.h>
#include <drivers/monitor.h>

#include <drivers/bridges/cgm_protocol.h>

CCgm_Sensor sCgm_Sensor(sI2C1);

CCgm_Sensor::CCgm_Sensor(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{
}

bool CCgm_Sensor::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CCgm_Sensor::Send_Command(Cgm_Sensor_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(Cgm_Slave_Address);

	ta << Cgm_Sensor_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CCgm_Sensor::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NCGM_Command cmd = static_cast<NCGM_Command>(input[0]);

	switch (cmd)
	{
	case NCGM_Command::Nop:
		break;

	case NCGM_Command::Read_Next:
	{
		auto& ta = mI2C.Begin_Transaction(Cgm_Slave_Address);

		ta << Cgm_Sensor_Cmd::Command_Start << Cgm_Sensor_Cmd::Read_Next_Value;

		mI2C.End_Transaction(ta);
		break;
	}
	case NCGM_Command::Read_Current:
	{
		auto& ta = mI2C.Begin_Transaction(Cgm_Slave_Address);

		ta << Cgm_Sensor_Cmd::Command_Start << Cgm_Sensor_Cmd::Read_Current_Value;

		mI2C.End_Transaction(ta);
		break;
	}
	}
}

void CCgm_Sensor::Close()
{
	if (!mOpened)
		return;

	mI2C.Close();

	mOpened = false;
}

bool CCgm_Sensor::Is_Opened() const
{
	return mOpened;
}

uint32_t CCgm_Sensor::Read(char*& buffer)
{
	TCGM_Value_Packet* cmd = reinterpret_cast<TCGM_Value_Packet*>(buffer);

	uint8_t bytes[4] = { 0 };

	Cgm_Sensor_Cmd command = Cgm_Sensor_Cmd::Read_Current_Value;

	if (cmd->header.cmd == NCGM_Command::Read_Next)
		command = Cgm_Sensor_Cmd::Read_Next_Value;

	// 1. Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta = mI2C.Begin_Transaction(Cgm_Slave_Address);

	// 2. Zapsání adresy registru (Read_Charge)
	ta << Cgm_Sensor_Cmd::Command_Start << command;

	// 3. Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta);

	// 4. Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& taRead = mI2C.Begin_Transaction(Cgm_Slave_Address | 1);  // Pøidání R bit (Read)

	// 6. Ukonèení transakce pro ètení
	mI2C.End_Transaction(taRead, true, true, 4);

	// 5. Ètení dat pøímo po pøepnutí na režim ètení
	taRead >> bytes[0] >> bytes[1] >> bytes[2] >> bytes[3];

	memcpy(&cmd->value, bytes, sizeof(float));

	return sizeof(cmd->value);
}

bool CCgm_Sensor::Test_Peripheral()
{
	return true;
}
