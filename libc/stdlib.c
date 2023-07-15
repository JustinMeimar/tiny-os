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
    char buf[256];
    // kprint("\n");
    kprint(int_to_ascii(n, buf));
}