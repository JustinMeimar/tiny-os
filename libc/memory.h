#ifndef MEMORY_H
#define MEMORY_H
#include "../kernel/types.h"
#include "./stdlib.h"

typedef struct 
{
    uint32_t *start;
} MemoryAllocator;

typedef enum
{
    free = 0,
    used = 1
} BlockState;

typedef struct BlockDescriptor BlockDescriptor;
struct BlockDescriptor 
{
    uint32_t *start;
    uint32_t size; 
    BlockDescriptor* next;
    BlockState state; 
};

extern char _kernel_end;

void init_memory_allocator();
void *malloc(uint32_t n_bytes);
void memcpy(void *dst, void *src, uint32_t bytes);

#endif