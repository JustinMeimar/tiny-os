#ifndef MEMORY_H
#define MEMORY_H
#include "../kernel/types.h"
#include "./stdlib.h"

typedef struct BlockDescriptor BlockDescriptor;
struct BlockDescriptor 
{
    void *start;
    uint32_t size; 
    uint8_t state; // 0000 00ab ... a == free / not free, b == last / not last
};

typedef struct 
{
    BlockDescriptor *first;
} MemoryAllocator;

extern char _kernel_end;

static void *get_memory_allocator();
void init_memory_allocator();

void *malloc(uint32_t n_bytes);
void free(void * ptr);

void memcpy(void *dst, void *src, uint32_t bytes);
void memset(void *dst, uint8_t value, uint32_t bytes);

//helper 
void dump_heap();
void memory_test();
#endif