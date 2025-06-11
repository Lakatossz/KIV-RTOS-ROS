#pragma once

#include <hal/intdef.h>
#include <drivers/gpio.h>

class CA810_Bubble_Sensor
{
private:

	// datovy pin pro vstup ze senzoru
	uint32_t mInput_Pin;

	// je driver pouzivan?
	bool mOpened;

public:

	CA810_Bubble_Sensor(uint32_t inputPin);

	// otevre kanal, inicializuje Air in line senzor, rezervuje piny
	bool Open();

	// uzavre kanal
	void Close();

	// je driver pouzivan?
	bool Is_Opened() const;

	bool Set_Event_Detect();

	void Wait_For_Event(IFile* file);

	bool Test_Peripheral();
};

extern CA810_Bubble_Sensor sA810_Bubble_Sensor;
