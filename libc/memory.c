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

/*
static void test_pointer_arithmetic() {
    // kprint("\n=========== TEST============\n");
    // kprint(" Base address of the memory allocator: "); 
    // kprint_int((uint32_t)mem_allocator);
    // kprint("\n Plus the size of a uint32_t: ");
    // kprint_int((uint32_t)(mem_allocator + sizeof(uint32_t)));
    // kprint("\n Size of unint32_t: ");
    // kprint_int(sizeof(uint32_t));
    // kprint("\n Increment Pointer");
    // kprint("\n Base Address: ");
    // kprint_int((uint32_t)(mem_allocator));
    // kprint("\n Base Address + 1: ");
    // kprint_int((uint32_t)(mem_allocator + 1));
    
    // kprint("\n=========== TEST============\n");
}  
*/ 

void *malloc(uint32_t n_bytes)
{ 
    MemoryAllocator *mem_allocator = get_memory_allocator();
       
    kprint("\nbase of heap: ");
    kprint_int((uint32_t)mem_allocator);

    void *heap_space = mem_allocator;
    if (mem_allocator->first == 0) //init the first block 
    {
        mem_allocator->first = (HEAP_ADDR + sizeof(MemoryAllocator));
    
        BlockDescriptor *init_block = (BlockDescriptor*)(mem_allocator->first); 
        init_block->start = (void *)(init_block) + sizeof(BlockDescriptor);
        init_block->size = n_bytes;
        init_block->state = 1; 
        init_block->next = 0;

        heap_space = init_block->start;

    } else {
        //traverse the block list to find the top of the heap
        kprint("\nelse"); 
        BlockDescriptor *cur_block = (BlockDescriptor*)mem_allocator->first; 
        while(cur_block->next != 0) 
        {
            if (cur_block->size < n_bytes)
            {
                //check if we can re-use a freed block
            }
            cur_block = cur_block->next;
        }

        //now cur_block has no following block
        void* heap_top = (void *)(cur_block->start) + cur_block->size;
        BlockDescriptor *new_block = (BlockDescriptor*)heap_top;
        new_block->start = heap_top + sizeof(BlockDescriptor);
        new_block->size = n_bytes;
        new_block->state = 1;
        new_block->next = 0;

        heap_space = new_block->start;
    }

    kprint("\ntop of heap:");
    kprint_int((uint32_t) heap_space);

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

void dump_heap()
{
    uint32_t bytes = 32; 
    void* heap = HEAP_ADDR;
    kprint("\n");
    for (uint32_t i = 0; i < bytes; i+=4)
    {
        kprint("|");
        kprint_int(*(uint32_t*)(heap + i));
        kprint(" ");
        kprint_int(*(uint32_t*)(heap + i + 1));
        kprint(" ");
        kprint_int(*(uint32_t*)(heap + i + 2));
        kprint(" ");
        kprint_int(*(uint32_t*)(heap + i + 3));
        kprint("|\n");
    }
}