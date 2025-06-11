#pragma once

#include <drivers/cgm_sensor.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

#include <drivers/monitor.h>

// virtualni soubor pro CGM senzoru
class CCgm_File final : public IFile
{
private:
	bool mOpened;

public:
	CCgm_File()
	: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CCgm_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		uint32_t result = sCgm_Sensor.Read(buffer);
		if (buffer == nullptr || result == 0)
			return 0;

		return result;
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		sCgm_Sensor.Process_External_Command(buffer, num);

		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sCgm_Sensor.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
    {
        return false;
    }
};

class CCgm_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{

		if (!sCgm_Sensor.Open())
			return nullptr;

		CCgm_File* f = new CCgm_File();

		return f;
	}
};

CCgm_FS_Driver fsCgm_FS_Driver;
