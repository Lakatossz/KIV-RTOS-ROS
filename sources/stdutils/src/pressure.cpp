#include <pressure.h>
#include <stdfile.h>
#include <stdstring.h>

#include <drivers/bridges/pressure_protocol.h>

CPressure::CPressure(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }
	, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CPressure::~CPressure()
{
	// pokud byl senzor tlaku otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CPressure::Is_Opened() const
{
	return mOpened;
}

bool CPressure::Test() const
{
	if (!mOpened)
		return false;

	TPressure_NonParametric_Packet pkt;
	pkt.header.cmd = NPressure_Command::Read;

	if (read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt)) != sizeof(float))
		return false;

	return true;
}

void CPressure::Init()
{
	if (!mOpened)
		return;

	TPressure_NonParametric_Packet pkt;
	pkt.header.cmd = NPressure_Command::Init;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CPressure::Reset()
{
	if (!mOpened)
		return;

	TPressure_NonParametric_Packet pkt;
	pkt.header.cmd = NPressure_Command::Reset;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CPressure::Read(float& target)
{
	if (!mOpened)
		return;

	TPressure_NonParametric_Packet pkt;
	pkt.header.cmd = NPressure_Command::Read;
	pkt.value = 10.0f;

	// Opravit float
	if (read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt)) != sizeof(pkt))
		return;

	target = pkt.value;

	return;
}
