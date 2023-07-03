#include "stdlib.h"

void memcpy(void *dst, void *src, uint32_t bytes)
{   
    uint32_t i = 0;
    char *c_dst = (char *)dst;
    char *c_src = (char *)src;
    
    while (i < bytes)
    {
        char byte = *(c_src + i);
        *(c_dst + i) = byte;
        i++;
    }
}

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

// tester methods
static uint8_t test_strlen()
{
    char *msg = "Hello, World!";
    if (strlen(msg) == 13) return 1;
        return 0;
}

static uint8_t test_memcpy()
{
    char *src_msg = "Hello, World!";
    char *dst_msg = "0000000000000";
    uint32_t len_msg = 13;

    memcpy(dst_msg, src_msg, len_msg + 1);

    for (uint8_t i = 0; i < len_msg; i++)
    {
        if (dst_msg[i] != src_msg[i]) {
            return 0;
        }
    }

    return 1;
}

void test_stdlib()
{
    if (test_strlen() == 1) {
        kprint_at("passed strlen", 8, 10);
    } else {
        kprint("failed strlen");
    }
    if (test_memcpy() == 1) {
        kprint_at("passed memcpy", 7, 10);
    } else {
        kprint("failed memcpy");
    }
}