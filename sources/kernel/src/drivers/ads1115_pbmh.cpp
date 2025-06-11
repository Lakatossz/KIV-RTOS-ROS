#include <drivers/ads1115_pbmh.h>
#include <memory/kernel_heap.h>
#include <stdstring.h>

#include <drivers/bridges/pressure_protocol.h>
#include <drivers/monitor.h>

CAds1115_Pbmh sAds1115_Pbmh(sI2C1);

CAds1115_Pbmh::CAds1115_Pbmh(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{
}

bool CAds1115_Pbmh::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CAds1115_Pbmh::Send_Command(Ads1115_Pbmh_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(Ads1115_Pbmh_Slave_Address);

	ta << Ads1115_Pbmh_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CAds1115_Pbmh::Close()
{
	if (!mOpened)
		return;

	mI2C.Close();

	mOpened = false;
}

bool CAds1115_Pbmh::Is_Opened() const
{
	return mOpened;
}

void CAds1115_Pbmh::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NPressure_Command cmd = static_cast<NPressure_Command>(input[0]);

	switch (cmd)
	{
		case NPressure_Command::Nop:
			break;

		case NPressure_Command::Init:
		{
			auto& ta = mI2C.Begin_Transaction(Ads1115_Pbmh_Slave_Address);

			ta << Ads1115_Pbmh_Cmd::Command_Start << Ads1115_Pbmh_Cmd::Write_Init;

			mI2C.End_Transaction(ta);
			break;
		}
		case NPressure_Command::Reset:
		{
			auto& ta = mI2C.Begin_Transaction(Ads1115_Pbmh_Slave_Address);

			ta << Ads1115_Pbmh_Cmd::Command_Start << Ads1115_Pbmh_Cmd::Write_Reset;

			mI2C.End_Transaction(ta);
			break;
		}
	}
}

uint32_t CAds1115_Pbmh::Read(char*& buffer)
{
	TPressure_NonParametric_Packet* cmd = reinterpret_cast<TPressure_NonParametric_Packet*>(buffer);

	uint8_t bytes[4] = { 0 };

	// 1. Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta = mI2C.Begin_Transaction(Ads1115_Pbmh_Slave_Address);

	// 2. Zapsání adresy registru (Read_Charge)
	ta << Ads1115_Pbmh_Cmd::Command_Start << Ads1115_Pbmh_Cmd::Read_Value;

	// 3. Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta);

	// 4. Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& taRead = mI2C.Begin_Transaction(Ads1115_Pbmh_Slave_Address | 1);  // Pøidání R bit (Read)

	// 5. Ètení dat pøímo po pøepnutí na režim ètení
	taRead >> bytes[0] >> bytes[1] >> bytes[2] >> bytes[3];

	// 6. Ukonèení transakce pro ètení
	mI2C.End_Transaction(taRead, true, true, 4);

	memcpy(&cmd->value, bytes, sizeof(float));

	return sizeof(cmd->value);
}

bool CAds1115_Pbmh::Test_Peripheral()
{
	return true;
}
