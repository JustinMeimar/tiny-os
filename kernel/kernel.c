#include "types.h"
#include "idt.h"
#include "isr.h"
#include "../drivers/display.h"

/**
 * Declare the array of GateDescriptors that constitute the IDT
 */
extern GateDescriptor idt_entries[256];

void main() 
{
    // screen stuffs 
    kprint("Hello, World");   
    
    // install the interupt handlers 
    install_isr(); 
    __asm__ __volatile__("int $2");
}