#include <monitor.h>

#include <stdfile.h>
#include <stdstring.h>

CMonitor::CMonitor(const char* path)
    : mHandle{ open(path, NFile_Open_Mode::Read_Write) }, mOpened(false)
{
    // nastavime priznak dle toho, co vrati open
    mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CMonitor::~CMonitor()
{
    // pokud byl displej otevreny, zavreme
    if (mOpened)
    {
        mOpened = false;
        close(mHandle);
    }
}

bool CMonitor::Is_Opened() const
{
    return mOpened;
}

bool CMonitor::Test() const
{
    if (!mOpened)
        return false;

    write(mHandle, "", sizeof(""));

    return true;
}


void CMonitor::Clear()
{
    if (!mOpened)
        return;

    ioctl(mHandle, NIOCtl_Operation::Enable_Event_Detection, nullptr);
}

void CMonitor::Put(const char* buf, uint16_t size)
{
    if (!mOpened)
        return;
    
    write(mHandle, buf, size * sizeof(buf));
}
