#ifndef ISR_H
#define ISR_H

#include "idt.h"
#include "../drivers/display.h"

/**
 * Interupt Service Routine handlers
 */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();

/**
 * Interupt Request handlers
 */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();

/**
 * Interupt codes 
 */
#define IRQ0 0x0
#define IRQ1 0x1
#define IRQ2 0x2
#define IRQ3 0x3

extern GateDescriptor idt_entries[256];

// install  
static void install_isr() {

    // install some interupt service routines into the IDT
    set_gate_descriptor(0, (uint32_t)irq0);
    set_gate_descriptor(1, (uint32_t)irq1); 
    set_gate_descriptor(2, (uint32_t)irq2);
    set_gate_descriptor(3, (uint32_t)irq3);

    // load the interupt descriptor table into the IDT register
    load_idt(idt_entries, sizeof(idt_entries));
}

// void handle_irq() 
// {
//     uint32_t irq_code;

//     char codes[2];
//     char base = '0';

//     codes[0] = ((char) irq_code) + base;
//     codes[1] = '\0';

//     __asm__ volatile (
//         "pop %%eax\n\t"
//         "mov %%eax, %0"
//         : "=r"(irq_code) 
//         :
//         : "%eax");

//     kprint("Recieved:");
//     kprint(codes);
// }

void handle_irq() 
{
    char codes[2];
    codes[1] = '\0';
    uint32_t irq_no;
    __asm__ (
        "movl %%ecx, %0" 
        : "=r"(irq_no)
        :
    ); // read the value from ecx register to irq_no
    codes[0] = (char) irq_no + '0'; 
    kprint(codes);
    // remaining code
}

static void dump_regs()
{
    uint32_t irq, idt, eax;

}

#endif