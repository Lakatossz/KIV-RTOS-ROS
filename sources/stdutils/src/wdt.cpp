#include <wdt.h>
#include <stdfile.h>
#include <stdstring.h>
#include <monitor.h>
#include <drivers/gpio.h>

CWdt::CWdt(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }
	, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));

	if (mOpened) {
		NGPIO_Interrupt_Type irtype = NGPIO_Interrupt_Type::Rising_Edge;
		ioctl(mHandle, NIOCtl_Operation::Enable_Event_Detection, &irtype);
	}
}

CWdt::~CWdt()
{
	// pokud byl displej otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CWdt::Is_Opened() const
{
	return mOpened;
}

bool CWdt::Test() const
{
	return true;
}

void CWdt::Kick()
{
	if (mOpened)
		return;

	write(mHandle, "1", 1);
	sleep(10);
	write(mHandle, "0", 1);
}
