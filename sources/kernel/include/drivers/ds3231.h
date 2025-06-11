#pragma once

#include <drivers/i2c.h>

// na teto adrese posloucha kazdy RTC
constexpr uint16_t Ds3231_Slave_Address = 0x68;

// -----------------------------------------------------------------------------------------------------------------
/// \brief Enumeration of different commands of the RTC.
// -----------------------------------------------------------------------------------------------------------------
enum class Ds3231_Cmd
{
	Command_Start = 0x00,               ///< Command start
	Data_Start = 0xC0,                  ///< Data start
	Data_Continue = 0x40,               ///< Data continue

	Read_Time = 0x81,					///< Read time
	Write_Reset = 0xA4,					///< Read value
	Write_Init = 0xA5,					///< Read value
};

class CDs3231
{
private:
	// I2C kanal
	CI2C& mI2C;
	// priznak otevreni RTC
	bool mOpened;

protected:
	// odesle I2C prikaz do RTC
	void Send_Command(Ds3231_Cmd cmd, uint8_t lowPart = 0);

public:
	CDs3231(CI2C& i2c);

	// otevre RTC
	bool Open();
	// zavre RTC
	void Close();
	// je RTC otevreny?
	bool Is_Opened() const;

	// zpracuje prikaz z externiho zdroje (napr. filesystem)
	void Process_External_Command(const char* input, uint32_t length);

	uint32_t Read(char* input);

	bool Test_Peripheral();
};

extern CDs3231 sDs3231;
