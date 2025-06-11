#pragma once

#include <drivers/i2c.h>

// na teto adrese posloucha kazdy senzor tlaku
constexpr uint16_t Ads1115_Pbmh_Slave_Address = 0x28;

enum class Ads1115_Pbmh_Cmd
{
	Command_Start = 0x00,               ///< Command start
	Data_Start = 0xC0,                  ///< Data start
	Data_Continue = 0x40,               ///< Data continue

	Read_Value = 0x81,					///< Read value
	Write_Reset = 0xA4,					///< Reset sensor
	Write_Init = 0xA5,					///< Initialise sensor
};

class CAds1115_Pbmh
{
private:
	// I2C kanal
	CI2C& mI2C;
	// buffer pro nactenou hodnotu
	uint8_t* mBuffer;
	// priznak otevreni
	bool mOpened;

protected:

	// odesle I2C prikaz do senzoru tlaku
	void Send_Command(Ads1115_Pbmh_Cmd cmd, uint8_t lowPart = 0);

public:

	CAds1115_Pbmh(CI2C& i2c);

	bool Open();

	void Close();

	bool Is_Opened() const;

	uint32_t Read(char*& buffer);

	// zpracuje prikaz z externiho zdroje (napr. filesystem)
	void Process_External_Command(const char* input, uint32_t length);

	bool Test_Peripheral();
};

extern CAds1115_Pbmh sAds1115_Pbmh;
