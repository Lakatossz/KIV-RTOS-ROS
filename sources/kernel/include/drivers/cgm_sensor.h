#pragma once

#include <drivers/i2c.h>
#include <drivers/gpio.h>

// na teto adrese posloucha kazdy displej CGM
constexpr uint16_t Cgm_Slave_Address = 0x78;

enum class Cgm_Sensor_Cmd
{
	Command_Start = 0x00,               ///< Command start
	Data_Start = 0xC0,                  ///< Data start
	Data_Continue = 0x40,               ///< Data continue

	Read_Next_Value = 0x81,				///< Read next glycemia value
	Read_Current_Value = 0xA5,			///< Read current glycemia value
};

class CCgm_Sensor
{
private:
	// I2C kanal
	CI2C& mI2C;
	// buffer pro nactenou hodnotu
	uint8_t* mBuffer;
	// priznak otevreni
	bool mOpened;

protected:

	// odesle I2C prikaz do cgm
	void Send_Command(Cgm_Sensor_Cmd cmd, uint8_t lowPart = 0);

public:

	CCgm_Sensor(CI2C& i2c);

	bool Open();

	void Close();

	bool Is_Opened() const;

	uint32_t Read(char*& buffer);

	// zpracuje prikaz z externiho zdroje (napr. filesystem)
	void Process_External_Command(const char* input, uint32_t length);

	bool Test_Peripheral();
};

extern CCgm_Sensor sCgm_Sensor;
