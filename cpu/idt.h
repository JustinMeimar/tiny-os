#ifndef IDT_H
#define IDT_H
#include "../kernel/types.h"

#define SELECTOR 0x08 // code segment
#define ATTRIBUTES 0x8E  // attributes for 10001110

/**
 * Interupt Descriptor Table is composed of [0-255] entries
 * of each 64-bit structs called GateDescriptor. So the 
 * size of the IDT is of max 256 x 8 bytes = 2K
 */
typedef struct 
{
    uint32_t size;
    uint32_t offset;
} __attribute__((packed)) IDTDescriptor;

/**
 * Gate Descriptor 
 */
typedef struct 
{
    uint16_t offset_1; // first part of the offset that 
    uint16_t selector; //A Segment Selector with points to a vliad code segment in the GDT
    uint8_t reserved; //zeros
    uint8_t attributes; // P[7] DPL[5:6] Zero[4] GateType[3:0]
    uint16_t offset_2; //MSB of the address
} __attribute__((packed)) GateDescriptor;

extern GateDescriptor idt_entries[256];

/** 
 * 32-bit protected move version of the IVT from 16-bit real mode.
 * Requires a working GDT before implementation.
 */
void load_idt(void *offset, uint32_t size);

void set_gate_descriptor(uint16_t n, uint32_t handler);

#endif