#include "memory.h"

void *HEAP_ADDR = &_kernel_end;

void init_memory_allocator()
{  
    MemoryAllocator *mem_allocator = (MemoryAllocator*)HEAP_ADDR;
    memset(HEAP_ADDR, 0, 256);
}

static void *get_memory_allocator()
{
    return (void*)(HEAP_ADDR);
}

void *malloc(uint32_t n_bytes)
{ 
    MemoryAllocator *mem_allocator = get_memory_allocator();

    void *heap_space = mem_allocator;
    if (mem_allocator->first == 0) //init the first block 
    {
        mem_allocator->first = (HEAP_ADDR + sizeof(MemoryAllocator));
    
        BlockDescriptor *init_block = (BlockDescriptor*)(mem_allocator->first); 
        init_block->start = (void *)(init_block) + sizeof(BlockDescriptor);
        init_block->size = n_bytes;
        init_block->state = 0xb00000011; //used, last

        heap_space = init_block->start;

    } else {
        //traverse the block list to find the top of the heap
        BlockDescriptor *cur_block = (BlockDescriptor*)mem_allocator->first;  //get first block on heap
        while((cur_block->state & 0x01) != 1) //while the cur block is not last 
        {
            void *next_block = (cur_block->start + cur_block->size);
            cur_block = (BlockDescriptor*)next_block;
        }

        // we have found the last block
        cur_block->state = (cur_block->state & 0xFE); //zero out the last (it is not last any more)
        
        void* heap_top = (void *)(cur_block->start) + cur_block->size;
        BlockDescriptor *new_block = (BlockDescriptor*)heap_top;
        new_block->start = heap_top + sizeof(BlockDescriptor);
        new_block->size = n_bytes;
        new_block->state = 1;

        heap_space = new_block->start;
    }

    return heap_space; 
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

void memset(void *dst, uint8_t value, uint32_t bytes)
{
    uint32_t i = 0;
    while (i < bytes)
    {
        *((char *)dst + i) = value;
        i++;
    } 
}