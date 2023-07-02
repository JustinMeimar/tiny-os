#include "types.h"
#include "idt.h"
#include "isr.h"
#include "../drivers/display.h"
#include "../libc/stdlib.h"

/**
 * Declare the array of GateDescriptors that constitute the IDT
 */
extern GateDescriptor idt_entries[256];

void main() 
{   
    // test stdlib
    test_stdlib();
    // screen stuffs 
    kprint("Hello, World");   
    
    // install the interupt handlers 
    install_isr(); 
    __asm__ __volatile__("int $1");
    
    // kprint("_DONE_INT_1_");   
    __asm__ __volatile__("int $2");
    
    // kprint("_DONE_INT_2_");   
    __asm__ __volatile__("int $0");
    
    // kprint("_DONE_INT_3_");   
    __asm__ __volatile__("int $3");

    kprint_at("testing the top row", 0, 0);
    kprint_at("testing print on the second row", 1, 0);
    kprint_at("testing print on the thirds row", 2, 0);

    scroll();
// 
    // kprint_at("testing the top row again", 0, 0);
    // kprint("123,123,123");
}