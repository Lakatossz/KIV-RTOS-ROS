#pragma once

#include <drivers/i2c.h>

// na teto adrese posloucha kazdy motor
constexpr uint16_t Pca9685_Mg996r_Slave_Address = 0x14;

// zakladni selekce prikazu motor
enum class Pca9685_Mg996r_Cmd
{
	Command_Start = 0x00,
	Data_Start = 0xC0,
	Data_Continue = 0x40,
	Push_Forward = 0x81,
	Push_Backwards = 0xA4,
	Reset_Position = 0xA5,
	Read_Status = 0xA6,
};

class CPca9685_Mg996r
{
private:
	// I2C kanal
	CI2C& mI2C;
	// priznak otevreni
	bool mOpened;

protected:
	// odesle I2C prikaz do motoru
	void Send_Command(Pca9685_Mg996r_Cmd cmd, uint8_t lowPart = 0);

public:
	CPca9685_Mg996r(CI2C& i2c);

	// otevre motor
	bool Open();
	// zavre motor
	void Close();
	// je motor otevreny?
	bool Is_Opened() const;

	void Reset();

	void Move_Forward(uint16_t steps);

	void Move_Backward(uint16_t steps);

	uint8_t Read_Status();

	// zpracuje prikaz z externiho zdroje (napr. filesystem)
	void Process_External_Command(const char* input, uint32_t length);

	bool Test_Peripheral();
};

extern CPca9685_Mg996r sPca9685_Mg996r;
