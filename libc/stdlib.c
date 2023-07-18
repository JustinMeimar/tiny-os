#include "stdlib.h"

uint32_t strlen(const char *msg)
{
    uint32_t i = 0;
    while (msg[i] != '\0')
    {
        i++;
    }
    return i;
}

char *int_to_ascii(uint32_t n, char *buffer)
{
    uint8_t i = 0;
    while (n >= 10)
    {
        char c = (n % 10);
        buffer[i] = ('0' + c);
        n = (n / 10);
        i++; 
    }
    buffer[i] = ('0'+ n);
    buffer[i+1] = '\0'; 
    reverse(buffer);
    return buffer;
}

char *hex_to_ascii(uint32_t n, char *buf)
{
    uint8_t i = 0;
    const char *hex_digits = "0123456789abcdef";
    do {
        buf[i] = hex_digits[n % 16];
        n /= 16;
        i++;
    } while (n != 0);

    buf[i] = '\0';
    reverse(buf);

    return buf;
}

void reverse(char *bytes)
{
    uint8_t i = 0;
    uint8_t j = strlen(bytes) - 1;
    while (i < j) 
    {
        char temp;
        temp = bytes[j];
        bytes[j] = bytes[i];
        bytes[i] = temp;
        i++;
        j--;
    }
}

void kprint_int(uint32_t n)
{
    char buf[128];
    kprint(int_to_ascii(n, buf));
}


void kprint_hex(uint32_t n)
{
    char buf[128];
    kprint(hex_to_ascii(n,buf));
    // kprint(hex_to_ascii(n,buf));
}

void test_krpint_from_stdlib(const char *str)
{
    kprint(str);
}