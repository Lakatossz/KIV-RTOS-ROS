#pragma once

#include <drivers/max6864.h>
#include <drivers/monitor.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro WDT
class CMax6864_File final : public IFile
{
private:
	bool mOpened;

public:

	CMax6864_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{
		//
	}

	~CMax6864_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		return 0; // neimplementovano
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		return num; // neimplementovano
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sMax6864.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation op, void* ctlptr) override
	{
		if (op == NIOCtl_Operation::Enable_Event_Detection) {
			return sMax6864.Set_Event_Detect();
		}

		return false;
	}
};

class CMax6864_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		// Bude jenom jeden

		if (!sMax6864.Open())
			return nullptr;

		if (mode != NFile_Open_Mode::Read_Write)
			return nullptr;

		CMax6864_File* f = new CMax6864_File();

		return f;
	}
};

CMax6864_FS_Driver fsMax6864_FS_Driver;
