#include "../../../include/utils/logger/logger.hpp"

void Debug(uint32_t logpipe, const char* string, uint16_t length)
{
	//auto now = m_rtc.Read();
	//write(logpipe, "[DEBUG] [", strlen("[DEBUG] ["));
	//write(m_logpipe, m_rtc.To_String(now), 20);
	//write(logpipe, "]: ", strlen("]: "));
	write(logpipe, string, length);
	write(logpipe, "\r\n", strlen("\r\n"));
}

void Info(uint32_t logpipe, const char* string, uint16_t length)
{
	//auto now = m_rtc.Read();
	write(logpipe, "[INFO] [", strlen("[INFO] ["));
	//write(m_logpipe, m_rtc.To_String(now), 20);
	write(logpipe, "]: ", strlen("]: "));
	write(logpipe, string, length);
	write(logpipe, "\r\n", strlen("\r\n"));
}

void Warning(uint32_t logpipe, const char* string, uint16_t length)
{
	//auto now = m_rtc.Read();
	write(logpipe, "[WARN] [", strlen("[WARN] ["));
	//write(m_logpipe, m_rtc.To_String(now), 20);
	write(logpipe, "]: ", strlen("]: "));
	write(logpipe, string, length);
	write(logpipe, "\r\n", strlen("\r\n"));
}

void Error(uint32_t logpipe, const char* string, uint16_t length)
{
	//auto now = m_rtc.Read();
	write(logpipe, "[ERROR] [", strlen("[ERROR] ["));
	//write(m_logpipe, m_rtc.To_String(now), 20);
	write(logpipe, "]: ", strlen("]: "));
	write(logpipe, string, length);
	write(logpipe, "\r\n", strlen("\r\n"));
}
