#include "types.h"
#include "../drivers/display.h"

/**
 * Interupt Descriptor Table is composed of [0-255] entries
 * of each 64-bit structs called GateDescriptor. So the 
 * size of the IDT is of max 256 x 8 bytes = 2K
 */
struct IDTDescriptor 
{
    uint32_t size;
    uint32_t offset;
} __attribute__((packed));

/**
 * Gate Descriptor 
 */
struct GateDescriptor
{
    uint16_t offset_1; // first part of the offset that 
    uint16_t selector; //A Segment Selector with points to a vliad code segment in the GDT
    uint8_t reserved; //zeros
    uint8_t attributes; // P[7] DPL[5:6] Zero[4] GateType[3:0]
    uint16_t offset_2; //MSB of the address
};

/** 
 * 32-bit protected move version of the IVT from 16-bit real mode.
 * Requires a working GDT before implementation.
 */
void load_idt()
{
    struct IDTDescriptor idtr;
    __asm__ volatile ("lidt %0" : : "m"(idtr)); //get the memory address of idtr and use as first arg to lidt
}

void main() 
{   
    char *video_mem = (char*) 0xb8000;

    *(video_mem) = 'J';
    *(video_mem + 2) = 'u';
    *(video_mem + 4) = 's';
    *(video_mem + 6) = 't';
    *(video_mem + 8) = 'i';
    *(video_mem + 10) = 'n';

    load_idt();
    
    uint16_t index = get_cursor_index();

    *(video_mem + (index*2)) = 'X';
}