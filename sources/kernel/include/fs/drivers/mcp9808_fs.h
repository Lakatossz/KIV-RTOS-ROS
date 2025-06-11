#pragma once

#include <drivers/mcp9808.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro senzoru teploty
class CMcp9808_File final : public IFile
{
private:
	bool mOpened;

public:

	CMcp9808_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CMcp9808_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		uint32_t result = sMcp9808.Read(buffer);

		if (buffer == nullptr)
			return 0;

		if (buffer == nullptr || result == 0)
			return 0;

		return result;
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		sMcp9808.Process_External_Command(buffer, num);

		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sMcp9808.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
	{
		return false;
	}
};

class CMcp9808_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		// Bude jenom jeden

		if (!sMcp9808.Open()) {
			return nullptr;
		}

		if (mode != NFile_Open_Mode::Read_Write)
			return nullptr;

		CMcp9808_File* f = new CMcp9808_File();

		return f;
	}
};

CMcp9808_FS_Driver fsMcp9808_FS_Driver;
