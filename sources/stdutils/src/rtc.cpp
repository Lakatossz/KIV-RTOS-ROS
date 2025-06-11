#include <rtc.h>
#include <stdfile.h>
#include <stdstring.h>
#include <monitor.h>

CRtc::CRtc(const char* path)
	: mHandle{ open(path, NFile_Open_Mode::Read_Write) }
	, mOpened(false)
{
	// nastavime priznak dle toho, co vrati open
	mOpened = (mHandle != static_cast<uint32_t>(-1));
}

CRtc::~CRtc()
{
	// pokud byl tlak otevreny, zavreme
	if (mOpened)
	{
		mOpened = false;
		close(mHandle);
	}
}

bool CRtc::Is_Opened() const
{
	return mOpened;
}

bool CRtc::Test() const
{
	return true;
}

void CRtc::Init()
{
	if (!mOpened)
		return;

	TRTC_NonParametric_Packet pkt;
	pkt.header.cmd = NRTC_Command::Init;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

void CRtc::Reset()
{
	if (!mOpened)
		return;

	TRTC_NonParametric_Packet pkt;
	pkt.header.cmd = NRTC_Command::Reset;

	write(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt));
}

CRtc::time_stamp CRtc::Read()
{
	if (!mOpened)
		return {};

	TRTC_NonParametric_Packet pkt;
	pkt.header.cmd = NRTC_Command::Read;
	pkt.date_time = {};

	CMonitor monitor("DEV:monitor");

	if (read(mHandle, reinterpret_cast<char*>(&pkt), sizeof(pkt)) != sizeof(pkt))
		return {};

	return Struct_To_Timestamp(pkt.date_time);
}

char* CRtc::Uint_To_Str(uint32_t value, char* buffer, uint8_t digits)
{
	// Pøevod èísla na øetìzec s pevnou šíøkou (doplnìní nulami zleva)
	buffer += digits;
	*buffer = '\0';
	for (int i = 0; i < digits; ++i)
	{
		*--buffer = '0' + (value % 10);
		value /= 10;
	}
	return buffer + digits; // vrací ukazatel za poslední znak
}

char* CRtc::To_String(const CRtc::time_stamp& ts)
{
	// Statický buffer (pozor na pøepis pøi dalším volání)
	static char buf[20]; // "YYYY-MM-DD HH:MM:SS\0"
	char* p = buf;
	p = Uint_To_Str(static_cast<uint32_t>(ts.day), p, 2);
	*p++ = '/';
	p = Uint_To_Str(static_cast<uint32_t>(ts.month + 1), p, 2);
	*p++ = '/';
	p = Uint_To_Str(static_cast<uint32_t>(ts.year + 1900), p, 4);
	*p++ = ' ';
	p = Uint_To_Str(static_cast<uint32_t>(ts.hour), p, 2);
	*p++ = ':';
	p = Uint_To_Str(static_cast<uint32_t>(ts.minute), p, 2);
	*p++ = ':';
	p = Uint_To_Str(static_cast<uint32_t>(ts.second), p, 2);
	*p = '\0';
	return buf;
}

bool CRtc::Bigger_Or_Equal(const CRtc::time_stamp& ts1, const CRtc::time_stamp& ts2)
{
	if (ts1.year != ts2.year)
		return ts1.year >= ts2.year;

	if (ts1.month != ts2.month)
		return ts1.month >= ts2.month;

	if (ts1.day != ts2.day)
		return ts1.day >= ts2.day;

	if (ts1.hour != ts2.hour)
		return ts1.hour >= ts2.hour;

	if (ts1.minute != ts2.minute)
		return ts1.minute >= ts2.minute;

	if (ts1.second != ts2.second)
		return ts1.second >= ts2.second;
}

CRtc::time_stamp CRtc::Struct_To_Timestamp(TRTC_Value value)
{
	CRtc::time_stamp t;
	t.second = value.second;
	t.minute = value.minute;
	t.hour = value.hour;
	t.day = value.day;
	t.month = value.month;
	t.year = value.year;
	return t;
}
