#include "memory.h"

#define USER_SPACE_START &_kernel_end
#define USER_SPACE_END (USER_SPACE_START + 0x100000)

static void *init_memory_allocator()
{
    MemoryAllocator *mem_allocator = (MemoryAllocator *)&_kernel_end;
    MemoryInfo info = { 
        .total_bytes = (USER_SPACE_END - USER_SPACE_START), 
        .free_blocks = 0, 
        .free_bytes = 0, 
        .allocated_blocks = 0, 
        .allocated_bytes = 0 
    };

    mem_allocator->mem_info = info;
    mem_allocator->first = (&_kernel_end + sizeof(MemoryAllocator));
}

static MemoryAllocator *get_memory_allocator()
{
    MemoryAllocator *mem_allocator = (MemoryAllocator *) &_kernel_end;
    if (mem_allocator->mem_info.allocated_blocks == 0) {
        init_memory_allocator();
    }

    return mem_allocator;
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
    MemoryInfo *mem_info = &mem_allocator->mem_info;

    if (mem_info->allocated_bytes + n_bytes > mem_info->total_bytes)
    {
        return -1; // insufficient space
    }

    if (mem_info->allocated_blocks == 0)
    { 
        // init first block
        BlockDescriptor *init_block = (BlockDescriptor*)(mem_allocator->first); 
        init_block->start = (void *)(init_block) + sizeof(BlockDescriptor);
        init_block->id = (mem_info->allocated_blocks + 1);
        init_block->size = n_bytes;
        init_block->state = 0x01;   //last block

        //update mem info
        mem_info->allocated_blocks++;
        mem_info->allocated_bytes += n_bytes;

        kprint("-- block id:");
        kprint_hex(init_block->id);
        kprint("\n");
        
        return init_block->start;

    } else {
    //     //traverse the block list to find the top of the heap

        BlockDescriptor *start_block = (BlockDescriptor*)mem_allocator->first;  //get first block on heap

        BlockDescriptor *cur_block = start_block;
        while((cur_block->state & 0x01) != 1) //while the cur block is not last 
        {
            if ((cur_block->state & 0x2) == 0x2)
            {
                if (n_bytes <= cur_block->size)
                {
                    memset(cur_block->start, 0, cur_block->size);
                    cur_block->state = (cur_block->state & 0xFD);
                    
                    kprint("-- block id:");
                    kprint_hex(cur_block->id);
                    kprint("\n");

                    return cur_block->start;
                }
            }
            void *next_block = (cur_block->start + cur_block->size);
            cur_block = (BlockDescriptor*)next_block;
        }

        cur_block->state = (cur_block->state & 0xFE);

        void* heap_top = (void *)(cur_block->start) + cur_block->size;
        BlockDescriptor *new_block = (BlockDescriptor*)heap_top;

        new_block->id = mem_info->allocated_blocks + 1;
        new_block->size = n_bytes;
        new_block->start = heap_top + sizeof(BlockDescriptor);
        new_block->state = 0x01;

        mem_info->allocated_bytes += n_bytes;
        mem_info->allocated_blocks++;
        
        kprint("-- block id:");
        kprint_hex(new_block->id);
        // kprint(" allocated blocks: ");
        // kprint_hex(mem_info->allocated_blocks);
        // kprint("\n");
        
        return new_block->start;
    }
}

void free(void *ptr)
{
    // state:  free--||--last_block  
    // fe: 0x 1111 1110  use to set the "last_block" bit to false
    // fd: 0x 1111 1101  use to set the "is_free" bit to false
    // ...
    // 02: 0x 0000 0010  use to set the "is free" bit to true
    // 01: 0x 0000 0001  use to set the "last block" bit to true
    kprint("=== Call Free ===\n");

    MemoryAllocator *mem_allocator = get_memory_allocator();
    MemoryInfo *mem_info = &mem_allocator->mem_info;
    BlockDescriptor *ptr_block = (BlockDescriptor*)(ptr - sizeof(BlockDescriptor));

    ptr_block->state = (ptr_block->state | 0x02); 
    mem_info->allocated_blocks--;
    mem_info->allocated_bytes -= ptr_block->size; 
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