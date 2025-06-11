#pragma once

#include <drivers/a810_bubble_sensor.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>

// virtualni soubor pro Air in Line senzor
class CA810_Bubble_Sensor_File final : public IFile
{
private:
	bool mOpened;

public:

	CA810_Bubble_Sensor_File()
		: IFile(NFile_Type_Major::Character), mOpened(true)
	{

	}

	~CA810_Bubble_Sensor_File()
	{
		Close();
	}

	virtual uint32_t Read(char* buffer, uint32_t num) override
	{
		return 0;
	}

	virtual uint32_t Write(const char* buffer, uint32_t num) override
	{
		return num;
	}

	virtual bool Close() override
	{
		if (!mOpened)
			return false;

		sA810_Bubble_Sensor.Close();
		mOpened = false;

		return true;
	}

	virtual bool IOCtl(NIOCtl_Operation op, void* ctlptr) override
	{
		if (op == NIOCtl_Operation::Enable_Event_Detection) {
			return sA810_Bubble_Sensor.Set_Event_Detect();
		}

		return false;
	}

	virtual bool Wait(uint32_t count) override
	{
		Wait_Enqueue_Current();
		sA810_Bubble_Sensor.Wait_For_Event(this);
		// zablokujeme, probudi nas az notify 
		sProcessMgr.Block_Current_Process();

		return false;
	}
};

class CA810_Bubble_Sensor_FS_Driver : public IFilesystem_Driver
{
public:
	virtual void On_Register() override
	{
		//
	}

	virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
	{
		// Bude jenom jeden

		if (!sA810_Bubble_Sensor.Open())
			return nullptr;

		if (mode != NFile_Open_Mode::Read_Only)
			return nullptr;

		CA810_Bubble_Sensor_File* f = new CA810_Bubble_Sensor_File();

		return f;
	}
};

CA810_Bubble_Sensor_FS_Driver fsA810_Bubble_Sensor_FS_Driver;
