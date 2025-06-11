#include <motor.h>
#include <stdfile.h>
#include <stdstring.h>

#include <drivers/bridges/motor_protocol.h>

CMotor::CMotor(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }
	, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CMotor::~CMotor()
{
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CMotor::Is_Opened() const
{
	return mOpened;
}

void CMotor::Init()
{
	if (!mOpened)
		return;

	TMotor_NonParametric_Packet pkt;
	pkt.header.cmd = NMotor_Command::Init;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CMotor::Reset()
{
	if (!mOpened)
		return;

	TMotor_NonParametric_Packet pkt;
	pkt.header.cmd = NMotor_Command::Reset;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CMotor::Get_Info()
{
	if (!mOpened)
		return;

	TMotor_NonParametric_Packet pkt;
	pkt.header.cmd = NMotor_Command::Reset;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

bool CMotor::Test()
{
	if (!mOpened)
		return false;

	uint8_t steps = 1;

	TMotor_Push_Packet pkt;
	pkt.header.cmd = NMotor_Command::Push_Forward;
	pkt.steps = steps;
	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));

	pkt.header.cmd = NMotor_Command::Push_Backward;
	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));

	TMotor_NonParametric_Packet read_pkt;
	read_pkt.header.cmd = NMotor_Command::Read_Status;

	uint32_t status = read(mHandle, reinterpret_cast<char*>(&read_pkt), sizeof(read_pkt)) != sizeof(read_pkt);

	if (status != 0)
		return false;

	return true;
}

void CMotor::Move_Forward(uint16_t steps)
{
	if (!mOpened)
		return;

	TMotor_Push_Packet pkt;
	pkt.header.cmd = NMotor_Command::Push_Forward;
	pkt.steps = steps;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CMotor::Move_Backward(uint16_t steps)
{
	if (!mOpened)
		return;

	TMotor_Push_Packet pkt;
	pkt.header.cmd = NMotor_Command::Push_Backward;
	pkt.steps = steps;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}