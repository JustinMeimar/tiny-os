#ifndef MEMORY_H
#define MEMORY_H
#include "../kernel/types.h"
#include "../libc/stdlib.h"

typedef struct BlockDescriptor BlockDescriptor;
struct BlockDescriptor 
{
    void *start;
    uint32_t id;
    uint32_t size; 
    uint8_t state; // 0000 00ab ... a == free / not free, b == last / not last
};

typedef struct {
    uint32_t total_bytes; // total blocks in the heap
    uint32_t free_blocks; // blocks currently free
    uint32_t free_bytes;
    uint32_t allocated_blocks; // blocks currently allocated
    uint32_t allocated_bytes; 
} MemoryInfo;

typedef struct 
{
    void *first;
    MemoryInfo mem_info;
} MemoryAllocator;


extern char _kernel_end;

static void *init_memory_allocator();
static MemoryAllocator *get_memory_allocator();
// void init_memory_allocator();

void *malloc(uint32_t n_bytes);
void free(void * ptr);

void memcpy(void *dst, void *src, uint32_t bytes);
void memset(void *dst, uint8_t value, uint32_t bytes);

//helper 
void dump_heap();
void memory_test();

#endif