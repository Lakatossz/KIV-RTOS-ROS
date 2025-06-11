#pragma once

#include <drivers/bq25120a.h>
#include <hal/peripherals.h>
#include <memory/kernel_heap.h>
#include <fs/filesystem.h>
#include <stdstring.h>
#include <drivers/bridges/battery_protocol.h>

// virtualni soubor pro bateriovy system
class CBattery_System_File final : public IFile
{
private:
    bool mOpened;

public:
    CBattery_System_File()
        : IFile(NFile_Type_Major::Character), mOpened(true)
    {
        //
    }

    ~CBattery_System_File()
    {
        Close();
    }

    virtual uint32_t Read(char* buffer, uint32_t num) override
    {
        const uint32_t needed = 6 * sizeof(uint32_t);
        if (num < needed) {
            return 0;
        }

        uint32_t offset = 0, i;
        
        TBattery_NonParametric_Packet* cmd = reinterpret_cast<TBattery_NonParametric_Packet*>(buffer);  // Ukazatel na strukturu

        uint32_t result = 0;

        switch (cmd->header.cmd) {
            case NBattery_Command::Read_Charge:
                result = sBattery_System_BQ25120A.Read_Charge(buffer);
                break;

            case NBattery_Command::Read_Voltage:
                result = sBattery_System_BQ25120A.Read_Voltage(buffer);
                break;

            case NBattery_Command::Read_Current:
                result = sBattery_System_BQ25120A.Read_Voltage(buffer);
                break;

            case NBattery_Command::Read_Temperature:
                result = sBattery_System_BQ25120A.Read_Voltage(buffer);
                break;
        }

        if (buffer == nullptr || result == 0)
            return 0;

        return result;
    }

    virtual uint32_t Write(const char* buffer, uint32_t num) override
    {
        sBattery_System_BQ25120A.Process_External_Command(buffer, num);

        return num;
    }

    virtual bool Close() override
    {
        if (!mOpened)
            return false;

        sBattery_System_BQ25120A.Close();
        mOpened = false;

        return IFile::Close();
    }

    virtual bool IOCtl(NIOCtl_Operation dir, void* ctlptr) override
    {
        return false;
    }
};

class CBattery_System_FS_Driver : public IFilesystem_Driver
{
public:
    virtual void On_Register() override
    {
        //
    }

    virtual IFile* Open_File(const char* path, NFile_Open_Mode mode) override
    {
        if (!sBattery_System_BQ25120A.Open())
            return nullptr;

        CBattery_System_File* f = new CBattery_System_File();

        return f;
    }
};

CBattery_System_FS_Driver fsBattery_System_FS_Driver;
