#ifndef ISR_H
#define ISR_H

#include "idt.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"

/**
 * Interupt Service Routine handlers */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
/**
 * Interupt Request handlers */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/**
 * Interupt codes */
#define IRQ0 0x20
#define IRQ1 0x21
#define IRQ2 0x22
#define IRQ3 0x23

typedef struct {
   uint32_t ds; /* Data segment selector */
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
   uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;
typedef void (*isr_t)(registers_t);

extern isr_t interrupt_handlers[256];

void install_isr();
extern void irq_handler(registers_t r); 
extern void isr_handler(registers_t r);
void register_interrupt_handler(uint8_t, isr_t handler);

static void remap_ports();

#endif