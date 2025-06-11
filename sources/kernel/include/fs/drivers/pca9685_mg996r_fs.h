#pragma once

#include <drivers/pca9685_mg996r.h>
#include <drivers/monitor.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro krokovy motor
class CPca9685_Mg996r_File final : public IFile
{
private:
	bool mOpened;

public:
	CPca9685_Mg996r_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CPca9685_Mg996r_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		return sPca9685_Mg996r.Read_Status();
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		sPca9685_Mg996r.Process_External_Command(buffer, num);
		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sPca9685_Mg996r.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
	{
		return false;
	}
};

class CPca9685_Mg996r_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		if (!sPca9685_Mg996r.Open())
			return nullptr;

		CPca9685_Mg996r_File* f = new CPca9685_Mg996r_File();

		return f;
	}
};

CPca9685_Mg996r_FS_Driver fsPca9685_Mg996r_FS_Driver;
