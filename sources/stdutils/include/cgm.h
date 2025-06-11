#pragma once

#include <hal/intdef.h>

// knihovni implementace CGM senzoru
class CCgm
{
private:
	// otevreny soubor cgm
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	// konstruktor - otevira soubor cgm
	CCgm(const char* path = "DEV:cgm");
	// destruktor - zavira soubor cgm
	~CCgm();

	// je soubor/cgm otevreny?
	bool Is_Opened() const;

	bool Test() const;

	void Init();

	void Reset();

	// Precte hodnotu cgm
	void Read(float& target);
};
