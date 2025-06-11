#pragma once

#include <drivers/gpio.h>

class CMax6864
{
private:
	// pin pro resetovani MCU
	uint32_t mReset_Pin;
	
	// datovy pin pro vstup z MCU
	uint32_t mWdi_Pin;

	// je driver pouzivan?
	bool mOpened;

public:

	CMax6864(uint32_t reset_Pin, uint32_t wdi_Pin);

	// otevre kanal, inicializuje Watchdog, rezervuje piny
	bool Open();

	// uzavre kanal
	void Close();

	// je driver pouzivan?
	bool Is_Opened() const;

	bool Set_Event_Detect();

	void Wait_For_Event(IFile* file);

	bool Test_Peripheral();
};

extern CMax6864 sMax6864;
