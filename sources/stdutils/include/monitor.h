#pragma once

#include <hal/intdef.h>

// knihovni implementace monitoru
class CMonitor
{
private:

    // otevreny soubor monitoru
    uint32_t mHandle;
    // byl soubor otevren?
    bool mOpened;

public:

    CMonitor(const char* path = "DEV:monitor");

    ~CMonitor();

    // je soubor/monitor otevreny?
    bool Is_Opened() const;

    bool Test() const;

    void Clear();

    void Put(const char* buf, uint16_t size);
};
