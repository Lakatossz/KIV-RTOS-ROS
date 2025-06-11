#pragma once

#include <hal/intdef.h>

// knihovni implementace senzoru tlaku
class CPressure
{
private:
	// otevreny soubor tlaku
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	// konstruktor - otevira soubor tlaku
	CPressure(const char* path = "DEV:press");
	// destruktor - zavira soubor tlaku
	~CPressure();

	// je soubor/tlak otevreny?
	bool Is_Opened() const;

	bool Test() const;

	void Init();

	void Reset();

	// Precte hodnotu tlaku
	void Read(float& target);
};