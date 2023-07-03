#include "isr.h"
isr_t interrupt_handlers[256];

void install_isr() 
{
    set_gate_descriptor(0, (uint32_t)isr0);
    set_gate_descriptor(1, (uint32_t)isr1);
    set_gate_descriptor(2, (uint32_t)isr2);
    set_gate_descriptor(3, (uint32_t)isr3);
    set_gate_descriptor(4, (uint32_t)isr4);
    set_gate_descriptor(5, (uint32_t)isr5);
    set_gate_descriptor(6, (uint32_t)isr6);
    set_gate_descriptor(7, (uint32_t)isr7);
    set_gate_descriptor(8, (uint32_t)isr8);
    set_gate_descriptor(9, (uint32_t)isr9);
    set_gate_descriptor(10, (uint32_t)isr10);
    set_gate_descriptor(11, (uint32_t)isr11);
    set_gate_descriptor(12, (uint32_t)isr12);
    set_gate_descriptor(13, (uint32_t)isr13);
    set_gate_descriptor(14, (uint32_t)isr14);
    set_gate_descriptor(15, (uint32_t)isr15);
    set_gate_descriptor(16, (uint32_t)isr16);
    set_gate_descriptor(17, (uint32_t)isr17);
    set_gate_descriptor(18, (uint32_t)isr18);
    set_gate_descriptor(19, (uint32_t)isr19);
    set_gate_descriptor(20, (uint32_t)isr20);
    set_gate_descriptor(21, (uint32_t)isr21);
    set_gate_descriptor(22, (uint32_t)isr22);
    set_gate_descriptor(23, (uint32_t)isr23);
    set_gate_descriptor(24, (uint32_t)isr24);
    set_gate_descriptor(25, (uint32_t)isr25);
    set_gate_descriptor(26, (uint32_t)isr26);
    set_gate_descriptor(27, (uint32_t)isr27);
    set_gate_descriptor(28, (uint32_t)isr28);
    set_gate_descriptor(29, (uint32_t)isr29);
    set_gate_descriptor(30, (uint32_t)isr30);
    set_gate_descriptor(31, (uint32_t)isr31);

    // Remap the PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    // Install the IRQs
    set_gate_descriptor(32, (uint32_t)irq0);
    set_gate_descriptor(33, (uint32_t)irq1);
    set_gate_descriptor(34, (uint32_t)irq2);
    set_gate_descriptor(35, (uint32_t)irq3);
    set_gate_descriptor(36, (uint32_t)irq4);
    set_gate_descriptor(37, (uint32_t)irq5);
    set_gate_descriptor(38, (uint32_t)irq6);
    set_gate_descriptor(39, (uint32_t)irq7);
    set_gate_descriptor(40, (uint32_t)irq8);
    set_gate_descriptor(41, (uint32_t)irq9);
    set_gate_descriptor(42, (uint32_t)irq10);
    set_gate_descriptor(43, (uint32_t)irq11);
    set_gate_descriptor(44, (uint32_t)irq12);
    set_gate_descriptor(45, (uint32_t)irq13);
    set_gate_descriptor(46, (uint32_t)irq14);
    set_gate_descriptor(47, (uint32_t)irq15);

    load_idt(idt_entries, sizeof(idt_entries) -1); // Load with ASM
}

void irq_handler(registers_t r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */

    // kprint("Recieved interupt request");
    
    if (interrupt_handlers[r.int_no] != 0) { 
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}

void isr_handler(registers_t r)
{
    kprint("Recieved Division by 0 error\n");
    return;
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void handle_isr()
{
    uint32_t isr;
    __asm__ __volatile__("movl %%ecx, %0" : "=r"(isr) : );
    switch (isr) {
        case 0:
            kprint("divide by 0"); break; 
        case 1: 
            kprint("isr 1"); break;
        case 2: 
            kprint("isr 2"); break;
        case 3: 
            kprint("isr 3"); break;
    }
}

static void remap_ports()
{
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    
    port_byte_out(0x21, 0x20);
    port_byte_out(0x21, 0x04);
    
    port_byte_out(0xA1, 0x28);
    port_byte_out(0xA1, 0x02);


    port_byte_out(0x21, 0x01);
    port_byte_out(0x21, 0x0);
    
    port_byte_out(0xA1, 0x01);
    port_byte_out(0xA1, 0x0); 
}