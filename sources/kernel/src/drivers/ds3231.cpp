#include <drivers/ds3231.h>
#include <memory/kernel_heap.h>
#include <stdstring.h>

#include <drivers/bridges/rtc_protocol.h>
#include <drivers/monitor.h>

CDs3231 sDs3231(sI2C1);

CDs3231::CDs3231(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{
}

bool CDs3231::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CDs3231::Send_Command(Ds3231_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(Ds3231_Slave_Address);

	ta << Ds3231_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CDs3231::Close()
{
	if (!mOpened)
		return;

	mI2C.Close();

	mOpened = false;
}

bool CDs3231::Is_Opened() const
{
	return mOpened;
}

void CDs3231::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NRTC_Command cmd = static_cast<NRTC_Command>(input[0]);

	switch (cmd)
	{
		case NRTC_Command::Nop:
			break;

		case NRTC_Command::Init:
		{
			auto& ta = mI2C.Begin_Transaction(Ds3231_Slave_Address);

			ta << Ds3231_Cmd::Command_Start << Ds3231_Cmd::Write_Init;

			mI2C.End_Transaction(ta);
			break;
		}
		case NRTC_Command::Reset:
		{
			auto& ta = mI2C.Begin_Transaction(Ds3231_Slave_Address);

			ta << Ds3231_Cmd::Command_Start << Ds3231_Cmd::Write_Reset;

			mI2C.End_Transaction(ta);
			break;
		}
	}
}

uint32_t CDs3231::Read(char* input)
{
	TRTC_Datetime_Packet* cmd = reinterpret_cast<TRTC_Datetime_Packet*>(input);

	// Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta_send = mI2C.Begin_Transaction(Ds3231_Slave_Address);

	// Zapsání adresy registru (Read_Charge)
	ta_send << Ds3231_Cmd::Command_Start << Ds3231_Cmd::Read_Time;

	// Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta_send);

	// Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& ta_recieve = mI2C.Begin_Transaction(Ds3231_Slave_Address | 1);  // Pøidání R bit (Read)

	// Ukonèení transakce pro ètení
	mI2C.End_Transaction(ta_recieve, true, true, 7);

	// Ètení dat pøímo po pøepnutí na režim ètení
	ta_recieve >> cmd->date_time.second
		>> cmd->date_time.minute
		>> cmd->date_time.hour
		>> cmd->date_time.day
		>> cmd->date_time.date
		>> cmd->date_time.month
		>> cmd->date_time.year;

	return sizeof(TRTC_Datetime_Packet);
}

bool CDs3231::Test_Peripheral()
{
	return true;
}
