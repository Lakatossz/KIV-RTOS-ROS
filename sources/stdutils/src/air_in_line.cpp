#include <air_in_line.h>
#include <stdfile.h>
#include <stdstring.h>
#include <monitor.h>
#include <drivers/gpio.h>


CAir_In_Line::CAir_In_Line(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Only) }
	, mOpened(false)
{
	
	CMonitor monitor = CMonitor();

	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));

	if (mOpened) {
		NGPIO_Interrupt_Type irtype = NGPIO_Interrupt_Type::Rising_Edge;
		ioctl(mHandle, NIOCtl_Operation::Enable_Event_Detection, &irtype);
	}
}

CAir_In_Line::~CAir_In_Line()
{
	// pokud byl displej otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CAir_In_Line::Is_Opened() const
{
	return mOpened;
}

bool CAir_In_Line::Test() const
{
	return true;
}

bool CAir_In_Line::Wait_For_Air()
{
	if (!mOpened)
		return false;

	if (wait(mHandle, 1, Indefinite) == NSWI_Result_Code::Fail)
		return false;

	return true;
}
