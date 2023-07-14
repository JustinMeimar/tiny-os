#include "memory.h"

#define HEAP_ADDR 0x8000;

void init_memory_allocator()
{
    void *heap_start = &_kernel_end;
    char buf[256];
    kprint(int_to_ascii(heap_start, buf));
    // MemoryAllocator mem_allocator;
    // mem_allocator.start = HEAP_ADDR;
}

void *malloc(uint32_t n_bytes)
{
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