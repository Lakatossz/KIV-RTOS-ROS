#pragma once

#include <drivers/ads1115_pbmh.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro senzor tlaku
class CAds1115_Pbmh_File final : public IFile
{
private:
	bool mOpened;

public:

	CAds1115_Pbmh_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CAds1115_Pbmh_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		uint32_t result = sAds1115_Pbmh.Read(buffer);

		if (buffer == nullptr || result == 0)
			return 0;

		return result;
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		sAds1115_Pbmh.Process_External_Command(buffer, num);

		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sAds1115_Pbmh.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
	{
		return false;
	}
};

class CAds1115_Pbmh_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		// Bude jenom jeden

		if (!sAds1115_Pbmh.Open())
			return nullptr;

		CAds1115_Pbmh_File* f = new CAds1115_Pbmh_File();

		return f;
	}
};

CAds1115_Pbmh_FS_Driver fsAds1115_Pbmh_FS_Driver;
