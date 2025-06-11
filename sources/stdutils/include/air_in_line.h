#pragma once

#include <hal/intdef.h>

// knihovni implementace Air in Line senzoru
class CAir_In_Line
{
private:
	// otevreny soubor air in line
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	// konstruktor - otevira soubor air in line
	CAir_In_Line(const char* path = "DEV:ail");
	// destruktor - zavira soubor air in line
	~CAir_In_Line();

	// je soubor/air in line otevreny?
	bool Is_Opened() const;

	bool Test() const;

	// Pocka na nalezeni vzduchu
	bool Wait_For_Air();
};