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

static void init_block_descriptor(BlockDescriptor* block, void* start, uint32_t size, uint8_t state)
{
    block->start = start;
    block->size = size;
    block->state = state;
}

void *malloc(uint32_t n_bytes)
{ 
    MemoryAllocator *mem_allocator = get_memory_allocator();

    void *heap_space = mem_allocator;
    if (mem_allocator->first == 0) //init the first block 
    {
        mem_allocator->first = (HEAP_ADDR + sizeof(MemoryAllocator));
    
        BlockDescriptor *init_block = (BlockDescriptor*)(mem_allocator->first); 
        void *start = (void *)(init_block) + sizeof(BlockDescriptor);
        init_block_descriptor(init_block, start, n_bytes, 0x01);

        heap_space = init_block->start;

    } else {
        //traverse the block list to find the top of the heap

        BlockDescriptor *cur_block = (BlockDescriptor*)mem_allocator->first;  //get first block on heap
        while((cur_block->state & 0x01) != 1) //while the cur block is not last 
        {
            // if (cur_block->state == 0x02 || cur_block->state == 0x03)
            if ((cur_block->state & 0x2) == 0x2)
            {
                if (n_bytes < cur_block->size)
                {
                    memset(cur_block->start, 0, cur_block->size);
                    cur_block->state = (cur_block->state & 0xFD);
                    heap_space = cur_block->start;
                    return;
                }
            }
            void *next_block = (cur_block->start + cur_block->size);
            cur_block = (BlockDescriptor*)next_block;
        }
        
        //zero out the last (it is not last any more) 
        cur_block->state = (cur_block->state & 0xFE); 

        //initialize the new block
        void* heap_top = (void *)(cur_block->start) + cur_block->size;
        BlockDescriptor *new_block = (BlockDescriptor*)heap_top;
        void* start = heap_top + sizeof(BlockDescriptor);
        init_block_descriptor(new_block, start, n_bytes, 0x01);

        heap_space = new_block->start;
    }

    return heap_space; 
}

void free(void *ptr)
{
    // state:  free--||--last_block  
    // fe: 0x 1111 1110  use to set the "last_block" bit to false
    // fd: 0x 1111 1101  use to set the "is_free" bit to false
    // ...
    // 02: 0x 0000 0010  use to set the "is free" bit to true
    // 01: 0x 0000 0001  use to set the "last block" bit to true

    MemoryAllocator *mem_allocator = get_memory_allocator();

    BlockDescriptor *ptr_block = (BlockDescriptor*)(ptr - sizeof(BlockDescriptor));
    ptr_block->state = (ptr_block->state | 0x02); 
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