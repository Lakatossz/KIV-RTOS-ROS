#pragma once

#include <hal/intdef.h>

// knihovni implementace senzoru teploty
class CTemperature
{
private:
	// otevreny soubor teploty
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	// konstruktor - otevira soubor teploty
	CTemperature(const char* path = "DEV:temp");
	// destruktor - zavira soubor teploty
	~CTemperature();

	// je soubor/teplota otevreny?
	bool Is_Opened() const;

	bool Test() const;

	// Precte hodnotu teploty
	void Read(float& target);
};