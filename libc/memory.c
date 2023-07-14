#include "memory.h"

#define HEAP_ADDR 0x8000;

void *malloc(uint32_t n_bytes)
{
    // uint32_t
    return 0;
}

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