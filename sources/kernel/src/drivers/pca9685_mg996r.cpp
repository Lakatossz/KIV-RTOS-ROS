#include <drivers/pca9685_mg996r.h>
#include <memory/kernel_heap.h>

#include <drivers/bridges/motor_protocol.h>
#include <drivers/monitor.h>

CPca9685_Mg996r sPca9685_Mg996r(sI2C1);

CPca9685_Mg996r::CPca9685_Mg996r(CI2C& i2c)
	: mI2C(i2c)
	, mOpened(false)
{

}

bool CPca9685_Mg996r::Open()
{
	if (!mI2C.Is_Opened() && !mI2C.Open())
		return false;

	mOpened = true;

	return true;
}

void CPca9685_Mg996r::Send_Command(Pca9685_Mg996r_Cmd cmd, uint8_t lowPart)
{
	auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

	ta << Pca9685_Mg996r_Cmd::Command_Start << (static_cast<uint8_t>(cmd) | lowPart);

	mI2C.End_Transaction(ta);
}

void CPca9685_Mg996r::Close()
{
	if (!mOpened)
		return;

	mI2C.Close();

	mOpened = false;
}

bool CPca9685_Mg996r::Is_Opened() const
{
	return mOpened;
}

void CPca9685_Mg996r::Reset()
{
	if (!mOpened)
		return;

	{
		auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

		ta << Pca9685_Mg996r_Cmd::Command_Start
			<< Pca9685_Mg996r_Cmd::Reset_Position;

		mI2C.End_Transaction(ta);
	}
}

void CPca9685_Mg996r::Move_Forward(uint16_t steps)
{
	if (!mOpened)
		return;

	uint8_t high = (steps >> 8) & 0xFF;
	uint8_t low = steps & 0xFF;

	// posleme prikaz s posunutim motoru vpred
	{
		auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

		ta << Pca9685_Mg996r_Cmd::Command_Start
			<< Pca9685_Mg996r_Cmd::Push_Forward 
			<< high 
			<< low;

		mI2C.End_Transaction(ta);
	}
}

void CPca9685_Mg996r::Move_Backward(uint16_t steps)
{
	if (!mOpened)
		return;

	uint8_t high = (steps >> 8) & 0xFF;
	uint8_t low = steps & 0xFF;

	// posleme prikaz s posunutim motoru vzad
	{
		auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

		ta << Pca9685_Mg996r_Cmd::Command_Start 
			<< Pca9685_Mg996r_Cmd::Push_Backwards
			<< high
			<< low;

		mI2C.End_Transaction(ta);
	}
}

uint8_t CPca9685_Mg996r::Read_Status()
{
	uint8_t status = 0;

	// 1. Zahájení transakce pro zápis (adresování registru pro ètení)
	auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

	// 2. Zapsání adresy registru (Read_Status)
	ta << Pca9685_Mg996r_Cmd::Command_Start << Pca9685_Mg996r_Cmd::Read_Status;

	// 3. Ukonèení transakce pro zápis
	mI2C.End_Transaction(ta);

	// 4. Zahájení transakce pro ètení (stejná adresa s R bit)
	auto& taRead = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address | 1);  // Pøidání R bit (Read)

	// 6. Ukonèení transakce pro ètení
	mI2C.End_Transaction(taRead, true, true, 1);

	// 5. Ètení dat pøímo po pøepnutí na režim ètení
	taRead >> status;

	sMonitor << "Status: " << static_cast<unsigned int>(status) << " \n";

	return status;
}

void CPca9685_Mg996r::Process_External_Command(const char* input, uint32_t length)
{
	if (length <= 0)
		return;

	NMotor_Command cmd = static_cast<NMotor_Command>(input[0]);

	switch (cmd)
	{
		case NMotor_Command::Nop:
			break;
		case NMotor_Command::Reset:
			Reset();
			break;
		case NMotor_Command::Push_Forward: {
			const TMotor_Push_Packet* pkt = reinterpret_cast<const TMotor_Push_Packet*>(input);
			if (pkt != nullptr) {
				Move_Forward(static_cast<uint16_t>(pkt->steps));
			}
			break;
		}
	
		case NMotor_Command::Push_Backward: {
			const TMotor_Push_Packet* pkt = reinterpret_cast<const TMotor_Push_Packet*>(input);
			if (pkt != nullptr) {
				Move_Backward(static_cast<uint16_t>(pkt->steps));
			}
			break;
		}

		case NMotor_Command::Read_Status: {
			const TMotor_NonParametric_Packet* pkt = reinterpret_cast<const TMotor_NonParametric_Packet*>(input);
			if (pkt != nullptr) {
				Read_Status();
			}
			break;
		}
	}
}

bool CPca9685_Mg996r::Test_Peripheral()
{
	if (!mOpened)
		return false;

	uint16_t steps = 1;

	uint8_t high = (steps >> 8) & 0xFF;
	uint8_t low = steps & 0xFF;

	// posleme prikaz s posunutim motoru vpred
	{
		auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

		ta << Pca9685_Mg996r_Cmd::Command_Start
			<< Pca9685_Mg996r_Cmd::Push_Forward 
			<< high 
			<< low;

		mI2C.End_Transaction(ta);
	}

	// posleme prikaz s posunutim motoru vzad
	{
		auto& ta = mI2C.Begin_Transaction(Pca9685_Mg996r_Slave_Address);

		ta << Pca9685_Mg996r_Cmd::Command_Start
			<< Pca9685_Mg996r_Cmd::Push_Backwards 
			<< high 
			<< low;

		mI2C.End_Transaction(ta);
	}

	return true;
}
