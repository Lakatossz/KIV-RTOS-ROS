#pragma once

#include <drivers/i2c.h>

// na teto adrese posloucha kazdy bateriovy system
constexpr uint16_t BQ25120A_Slave_Address = 0x6B;

// -----------------------------------------------------------------------------------------------------------------
/// \brief Enumeration of different commands of the Battery system.
// -----------------------------------------------------------------------------------------------------------------
enum class BQ25120A_Cmd
{
	Command_Start = 0x00,               ///< Command start
	Data_Start = 0xC0,                  ///< Data start
	Data_Continue = 0x40,               ///< Data continue
	Read_Charge = 0x81,					///< Read value
	Read_Voltage = 0xA5,				///< Read value
	Read_Current = 0xA6,				///< Read value
	Read_Temperature = 0xA7,			///< Read value
	Read_Errors = 0xAE,					///< Read value
	Read_Info = 0xAF,					///< Read value
	Write_Reset = 0xE3,					///< Read value
};

class CBattery_System_BQ25120A
{
private:
	// I2C kanal
	CI2C& mI2C;
	// priznak otevreni
	bool mOpened;

protected:
	// odesle I2C prikaz do baterie
	void Send_Command(BQ25120A_Cmd cmd, uint8_t lowPart = 0);

private:

	void Write_Reset();

	uint32_t Read(BQ25120A_Cmd cmd, char*& buffer);

public:
	CBattery_System_BQ25120A(CI2C& i2c);

	// otevre baterii
	bool Open();

	// zavre baterii
	void Close();

	// je baterie otevrena?
	bool Is_Opened() const;

	// zpracuje prikaz z externiho zdroje (napr. filesystem)
	void Process_External_Command(const char* input, uint32_t length);

	uint32_t Read_Charge(char*& buffer);

	uint32_t Read_Voltage(char*& buffer);

	uint32_t Read_Current(char*& buffer);

	uint32_t Read_Temperature(char*& buffer);

	uint32_t Read_Errors(char*& buffer);

	uint32_t Read_Info(char*& buffer);

	bool Test_Peripheral();
};

extern CBattery_System_BQ25120A sBattery_System_BQ25120A;
