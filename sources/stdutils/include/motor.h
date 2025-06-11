#pragma once

#include <hal/intdef.h>

// knihovni implementace krokoveho motoru
class CMotor
{
private:
	// otevreny soubor motoru
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:
	// konstruktor - otevira soubor motoru
	CMotor(const char* path = "DEV:motor");
	// destruktor - zavira soubor motoru
	~CMotor();

	// je soubor/displej otevreny?
	bool Is_Opened() const;

	void Init();

	void Reset();

	void Get_Info();

	bool Test();

	void Move_Forward(uint16_t steps);

	void Move_Backward(uint16_t steps);
};