#pragma once

#include <hal/intdef.h>

#include <drivers/bridges/rtc_protocol.h>

// knihovni implementace RTC
class CRtc
{
private:
	// otevreny soubor rtc
	uint32_t mHandle;
	// byl soubor otevren?
	bool mOpened;

public:

	struct time_stamp
    {
        uint8_t year;   // > 1900
        uint8_t month;  // 1-12
        uint8_t day;    // 1-31
        uint8_t hour;   // 0-23
        uint8_t minute; // 0-59
        uint8_t second; // 0-59
    };

	// konstruktor - otevira soubor rtc
	CRtc(const char* path = "DEV:rtc");
	// destruktor - zavira soubor rtc
	~CRtc();

	// je soubor/rtc otevreny?
	bool Is_Opened() const;

	bool Test() const;

	void Init();

	void Reset();

	// Precte hodnotu rtc
	time_stamp Read();

    char* Uint_To_Str(uint32_t value, char* buffer, uint8_t digits);

	char* To_String(const CRtc::time_stamp& ts);

	bool Bigger_Or_Equal(const CRtc::time_stamp& ts1, const CRtc::time_stamp& ts2);

private:

	CRtc::time_stamp Struct_To_Timestamp(TRTC_Value value);
};