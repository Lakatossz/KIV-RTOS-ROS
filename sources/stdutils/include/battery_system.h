#pragma once

#include <hal/intdef.h>

#include <drivers/bridges/battery_protocol.h>

// knihovni implementace baterioveho systemu
class CBattery_System
{
private:

	// otevreny bateriovy system
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:
	// konstruktor - otevira soubor baterioveho systemu
	CBattery_System(const char* path = "DEV:battery");
	// destruktor - zavira soubor baterioveho systemu
	~CBattery_System();

	// je soubor/bateriovy system otevreny?
	bool Is_Opened() const;

	bool Test();

	// vrati aktualni hodnotu nabiti baterioveho systemu
	void Get_Charge(float& target);

	// vrati aktualni hodnotu napeti baterioveho systemu
	void Get_Voltage(float& target);

	// vrati aktualni hodnotu proudu baterioveho systemu
	void Get_Current(float& target);

	// vrati aktualni hodnotu teploty baterioveho systemu
	void Get_Temperature(float& target);

	// vrati aktualni hodnoty chyb baterioveho systemu
	void Get_Errors(float& target);

	// vrati aktualni hodnotu informaci o bateriovem systemu
	void Get_Info(float& target);

	// vyresetuje bateriovy system
	void Reset();

private:

	// vrati aktualni hodnotu baterioveho systemu zadaneho podle prikazu
	void Get_Value(NBattery_Command command, float& target);
};
