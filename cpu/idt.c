#include "idt.h"

GateDescriptor idt_entries[256];

void load_idt(void *offset, uint32_t size)
{
    struct {
        uint16_t size;
        void *base;
    } __attribute__((packed)) IDTR = {size, offset};

    __asm__ volatile ("lidt %0" : : "m"(IDTR)); //get the memory address of idtr and use as first arg to lidt
}

void set_gate_descriptor(uint16_t n, uint32_t handler)
{
    idt_entries[n].offset_1 = (handler & 0xFFFF);
    idt_entries[n].selector = SELECTOR;
    idt_entries[n].reserved = 0;
    idt_entries[n].attributes = ATTRIBUTES;
    idt_entries[n].offset_2 = (handler >> 16) & 0xFFFF;
}