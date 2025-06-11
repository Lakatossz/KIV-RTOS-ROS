#include <battery_system.h>
#include <stdfile.h>
#include <stdstring.h>

CBattery_System::CBattery_System(const char* path)
    : mHandle{ open(path, NFile_Open_Mode::Write_Only) }, mOpened(false)
{
    // nastavime priznak dle toho, co vrati open
    mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CBattery_System::~CBattery_System()
{
    // pokud byl bateriovy system otevreny, zavreme ho
    if (mOpened)
    {
        mOpened = false;
        close(mHandle);
    }
}

bool CBattery_System::Is_Opened() const
{
    return mOpened;
}

bool CBattery_System::Test()
{
    float target = 0.0f;

    Get_Value(NBattery_Command::Read_Charge, target);
    return true;
}

void CBattery_System::Get_Charge(float& target)
{
    Get_Value(NBattery_Command::Read_Charge, target);
}

void CBattery_System::Get_Voltage(float& target)
{
    Get_Value(NBattery_Command::Read_Voltage, target);
}

void CBattery_System::Get_Current(float& target)
{
    Get_Value(NBattery_Command::Read_Current, target);
}

void CBattery_System::Get_Temperature(float& target)
{
    Get_Value(NBattery_Command::Read_Temperature, target);
}

void CBattery_System::Reset()
{
    if (!mOpened)
        return;

    TBattery_NonParametric_Packet pkt;
    pkt.header.cmd = NBattery_Command::Reset;

    write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CBattery_System::Get_Value(NBattery_Command command, float& target)
{
    if (!mOpened)
        return;

    TBattery_NonParametric_Packet pkt;
    pkt.header.cmd = command;

    // Opravit float
    read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));

    target = pkt.value;
}
