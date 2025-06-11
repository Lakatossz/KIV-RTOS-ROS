#include <drivers/bq25120a.h>
#include <drivers/monitor.h>
#include <memory/kernel_heap.h>
#include <stdstring.h>

#include <drivers/bridges/battery_protocol.h>

CBattery_System_BQ25120A sBattery_System_BQ25120A(sI2C1);

CBattery_System_BQ25120A::CBattery_System_BQ25120A(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{
}

bool CBattery_System_BQ25120A::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CBattery_System_BQ25120A::Send_Command(BQ25120A_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(BQ25120A_Slave_Address);

	//ta << Battery_System_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CBattery_System_BQ25120A::Close()
{
	if (!mOpened)
		return;

	// posleme prikaz z vypnuti baterie
	{
		auto& ta = mI2C.Begin_Transaction(BQ25120A_Slave_Address);

		//ta << Battery_System_Cmd::Command_Start << Battery_System_Cmd::Display_Off;

		mI2C.End_Transaction(ta);
	}

	mI2C.Close();

	mOpened = false;
}

bool CBattery_System_BQ25120A::Is_Opened() const
{
	return mOpened;
}



void CBattery_System_BQ25120A::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NBattery_Command cmd = static_cast<NBattery_Command>(input[0]);

	switch (cmd)
	{
		case NBattery_Command::Reset:
		{
			Write_Reset();
			break;
		}
	}
}

uint32_t CBattery_System_BQ25120A::Read_Charge(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Charge, buffer);
}

uint32_t CBattery_System_BQ25120A::Read_Voltage(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Voltage, buffer);
}

uint32_t CBattery_System_BQ25120A::Read_Current(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Current, buffer);
}

uint32_t CBattery_System_BQ25120A::Read_Temperature(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Temperature, buffer);
}

uint32_t CBattery_System_BQ25120A::Read_Errors(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Errors, buffer);
}

uint32_t CBattery_System_BQ25120A::Read_Info(char*& buffer)
{
	return Read(BQ25120A_Cmd::Read_Info, buffer);
}

uint32_t CBattery_System_BQ25120A::Read(BQ25120A_Cmd i2c_cmd, char*& buffer)
{
	uint8_t bytes[4] = { 0 };

	TBattery_NonParametric_Packet* cmd = reinterpret_cast<TBattery_NonParametric_Packet*>(buffer);

	// 1. Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta = mI2C.Begin_Transaction(BQ25120A_Slave_Address);

	// 2. Zapsání adresy registru (Read_Charge)
	ta << BQ25120A_Cmd::Command_Start << i2c_cmd;

	// 3. Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta);

	// 4. Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& taRead = mI2C.Begin_Transaction(BQ25120A_Slave_Address | 1);  // Pøidání R bit (Read)

	// 6. Ukonèení transakce pro ètení
	mI2C.End_Transaction(taRead, true, true);

	// 5. Ètení dat pøímo po pøepnutí na režim ètení
	taRead >> bytes[0] >> bytes[1] >> bytes[2] >> bytes[3];

	memcpy(&cmd->value, bytes, sizeof(float));

	return sizeof(cmd->value);
}

void CBattery_System_BQ25120A::Write_Reset()
{
	auto& ta = mI2C.Begin_Transaction(BQ25120A_Slave_Address);

	ta << BQ25120A_Cmd::Command_Start
		<< BQ25120A_Cmd::Write_Reset;

	mI2C.End_Transaction(ta);
}

bool CBattery_System_BQ25120A::Test_Peripheral()
{
	return true;
}
