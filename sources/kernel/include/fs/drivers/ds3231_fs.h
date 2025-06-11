#pragma once

#include <drivers/ds3231.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro RTC
class CDs3231_File final : public IFile
{
private:
	bool mOpened;

public:

	CDs3231_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CDs3231_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		uint32_t result = sDs3231.Read(buffer);
		if (buffer == nullptr || result == 0)
			return 0;

		return result;
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sDs3231.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
	{
		return false;
	}
};

class CDs3231_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		// Bude jenom jeden

		if (!sDs3231.Open())
			return nullptr;

		CDs3231_File* f = new CDs3231_File();

		return f;
	}
};

CDs3231_FS_Driver fsDs3231_FS_Driver;
