#pragma once

#include <hal/intdef.h>

// knihovni implementace WDT
class CWdt
{
private:
	// otevreny soubor wdt
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	// konstruktor - otevira soubor wdt
	CWdt(const char* path = "DEV:wdt");
	// destruktor - zavira soubor wdt
	~CWdt();

	// je soubor/wdt otevreny?
	bool Is_Opened() const;

	bool Test() const;

	// Ohlasi se wdt
	void Kick();
};