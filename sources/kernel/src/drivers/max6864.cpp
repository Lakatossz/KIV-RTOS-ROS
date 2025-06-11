#include <drivers/max6864.h>
#include <drivers/monitor.h>

#include <stdfile.h>

CMax6864 sMax6864(23, 24);

CMax6864::CMax6864(uint32_t reset_Pin, uint32_t wdi_Pin)
	: mReset_Pin(reset_Pin)
	, mWdi_Pin(wdi_Pin)
{
	//
}

bool CMax6864::Open()
{
	if (mOpened)
		return false;

	if (!sGPIO.Reserve_Pin(mReset_Pin, true, false))
		return false;

	if (!sGPIO.Reserve_Pin(mWdi_Pin, false, true)) {
		sGPIO.Free_Pin(mReset_Pin, true, false);
		return false;
	}

	sGPIO.Set_GPIO_Function(mWdi_Pin, NGPIO_Function::Output);

	mOpened = true;

	return true;
}

void CMax6864::Close()
{
	if (!mOpened)
		return;

	// prepneme piny na vstupni (setreni energii)
	sGPIO.Set_GPIO_Function(mReset_Pin, NGPIO_Function::Output);
	sGPIO.Set_GPIO_Function(mWdi_Pin, NGPIO_Function::Input);

	sGPIO.Disable_Event_Detect(mReset_Pin, NGPIO_Interrupt_Type::Falling_Edge);

	// a vratime je
	sGPIO.Free_Pin(mReset_Pin, true, false);
	sGPIO.Free_Pin(mWdi_Pin, false, true);

	mOpened = false;
}

bool CMax6864::Is_Opened() const
{
	return mOpened;
}

bool CMax6864::Set_Event_Detect()
{
	if (!mOpened)
		return false;

	sGPIO.Set_GPIO_Function(mReset_Pin, NGPIO_Function::Input);
	sGPIO.Enable_Event_Detect(mReset_Pin, NGPIO_Interrupt_Type::Rising_Edge);

	return true;
}

bool CMax6864::Test_Peripheral()
{
	return true;
}
