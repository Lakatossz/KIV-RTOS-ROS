#include <stdstring.h>

namespace
{
    const char CharConvArr[] = "0123456789ABCDEF";
}

void itoa(unsigned int input, char* output, unsigned int base)
{
	int i = 0;

	while (input > 0)
	{
		output[i] = CharConvArr[input % base];
		input /= base;
		i++;
	}

    if (i == 0)
    {
        output[i] = CharConvArr[0];
        i++;
    }

	output[i] = '\0';
	i--;

	for (int j = 0; j <= i/2; j++)
	{
		char c = output[i - j];
		output[i - j] = output[j];
		output[j] = c;
	}
}

int atoi(const char* input)
{
	int output = 0;

	while (*input != '\0')
	{
		output *= 10;
		if (*input > '9' || *input < '0')
			break;

		output += *input - '0';

		input++;
	}

	return output;
}

char* strncpy(char* dest, const char *src, int num)
{
	int i;

	for (i = 0; i < num && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < num; i++)
		dest[i] = '\0';

   return dest;
}

int strncmp(const char *s1, const char *s2, int num)
{
	unsigned char u1, u2;
  	while (num-- > 0)
    {
      	u1 = (unsigned char) *s1++;
     	u2 = (unsigned char) *s2++;
      	if (u1 != u2)
        	return u1 - u2;
      	if (u1 == '\0')
        	return 0;
    }

  	return 0;
}

int strlen(const char* s)
{
	int i = 0;

	while (s[i] != '\0')
		i++;

	return i;
}

void bzero(void* memory, int length)
{
	char* mem = reinterpret_cast<char*>(memory);

	for (int i = 0; i < length; i++)
		mem[i] = 0;
}

void memcpy(const void* src, void* dst, int num)
{
	const char* memsrc = reinterpret_cast<const char*>(src);
	char* memdst = reinterpret_cast<char*>(dst);

	for (int i = 0; i < num; i++)
		memdst[i] = memsrc[i];
}

void* memset(void* b, int c, int len)
{
	int i;
	unsigned char* p = reinterpret_cast<unsigned char*>(b);
	i = 0;
	while (len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return(b);
}

/*void ftoa(float f, char* buffer, int precision = 3) {
	// Zpracování znaménka
	int index = 0;
	if (f < 0) {
		buffer[index++] = '-';
		f = -f;
	}

	// Celá èást
	int whole = static_cast<int>(f);
	float frac = f - whole;

	// Pøevod celé èásti na øetìzec (obrácenì)
	int temp = whole;
	int digits = 0;
	do {
		digits++;
		temp /= 10;
	} while (temp);

	// Uložení celé èásti (od nejvyššího øádu)
	for (int d = digits - 1; d >= 0; d--) {
		int pow10 = 1;
		for (int p = 0; p < d; p++) pow10 *= 10;
		buffer[index++] = '0' + (whole / pow10) % 10;
	}

	// Desetinná teèka a desetinná èást
	if (precision > 0) {
		buffer[index++] = '.';
		for (int p = 0; p < precision; p++) {
			frac *= 10;
			int digit = static_cast<int>(frac);
			buffer[index++] = '0' + digit;
			frac -= digit;
		}
	}

	// Ukonèení øetìzce
	buffer[index] = '\0';
}*/

void ftoa(float f, char* buffer, int precision = 3) {
	int index = 0;

	// Znaménko
	if (f < 0) {
		buffer[index++] = '-';
		f = -f;
	}

	// Zaokrouhlení pro pøesnìjší výsledek
	float round_factor = 0.5f;
	for (int i = 0; i < precision; i++) round_factor /= 10.0f;
	f += round_factor;

	// Celá èást - jednodušší zpùsob
	uint32_t whole = (uint32_t)f;
	if (whole == 0) {
		buffer[index++] = '0';
	}
	else {
		// Pøevod pøes doèasný buffer a obrácení
		char temp[12];
		int temp_idx = 0;
		uint32_t num = whole;
		while (num > 0) {
			temp[temp_idx++] = '0' + (num % 10);
			num /= 10;
		}
		for (int i = temp_idx - 1; i >= 0; i--) {
			buffer[index++] = temp[i];
		}
	}

	// Desetinná èást
	if (precision > 0) {
		buffer[index++] = '.';
		f -= whole;
		for (int i = 0; i < precision; i++) {
			f *= 10;
			int digit = static_cast<int>(f);
			buffer[index++] = '0' + digit;
			f -= digit;
		}
	}

	buffer[index] = '\0';
}
