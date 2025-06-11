#include <cgm.h>
#include <stdfile.h>
#include <stdstring.h>

#include <monitor.h>

#include <drivers/bridges/cgm_protocol.h>

CCgm::CCgm(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CCgm::~CCgm()
{
	// pokud byl cgm senzor otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CCgm::Is_Opened() const
{
	return mOpened;
}

bool CCgm::Test() const
{
	if (!mOpened)
		return false;

	TCGM_NonParametric_Packet pkt;
	pkt.header.cmd = NCGM_Command::Read_Current;

	if (read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt)) != sizeof(float))
		return false;

	return true;
}

void CCgm::Init()
{
	if (!mOpened)
		return;

	TCGM_NonParametric_Packet pkt;
	pkt.header.cmd = NCGM_Command::Init;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CCgm::Reset()
{
	if (!mOpened)
		return;

	TCGM_NonParametric_Packet pkt;
	pkt.header.cmd = NCGM_Command::Reset;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CCgm::Read(float& target)
{
	if (!mOpened)
		return;

	TCGM_NonParametric_Packet pkt;
	pkt.header.cmd = NCGM_Command::Read_Next;
	pkt.value = 10.0f;

	if (read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt)) != sizeof(pkt))
		return;

	target = pkt.value;

	return;
}
