#include <temperature.h>
#include <stdfile.h>
#include <stdstring.h>
#include <monitor.h>

CTemperature::CTemperature(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }
	, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CTemperature::~CTemperature()
{
	// pokud byl displej otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CTemperature::Is_Opened() const
{
	return mOpened;
}

bool CTemperature::Test() const
{
	return true;
}

void CTemperature::Read(float& target)
{
	if (!mOpened)
		return;

	target = 20.0f;

	// Opravit float
	read(mHandle, reinterpret_cast<char*>(&target), sizeof(target));
}
