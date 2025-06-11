#include <drivers/a810_bubble_sensor.h>
#include <drivers/monitor.h>

CA810_Bubble_Sensor sA810_Bubble_Sensor(26);

CA810_Bubble_Sensor::CA810_Bubble_Sensor(uint32_t inputPin)
	: mInput_Pin(inputPin)
{
	//
}

bool CA810_Bubble_Sensor::Open()
{
	if (mOpened)
		return false;

	mOpened = true;

	return true;
}

void CA810_Bubble_Sensor::Close()
{
	if (!mOpened)
		return;

	mOpened = false;
}

bool CA810_Bubble_Sensor::Is_Opened() const
{
	return mOpened;
}

bool CA810_Bubble_Sensor::Set_Event_Detect()
{
	if (!mOpened)
		return false;

	sGPIO.Set_GPIO_Function(mInput_Pin, NGPIO_Function::Input);
	sGPIO.Enable_Event_Detect(mInput_Pin, NGPIO_Interrupt_Type::Falling_Edge);

	return true;
}

void CA810_Bubble_Sensor::Wait_For_Event(IFile *file)
{
	sGPIO.Wait_For_Event(file, mInput_Pin);
}

bool CA810_Bubble_Sensor::Test_Peripheral()
{
	return true;
}
