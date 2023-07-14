#include "types.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../libc/stdlib.h"
#include "../libc/memory.h"

/**
 * Declare the array of GateDescriptors that constitute the IDT
 */
extern GateDescriptor idt_entries[256];
static void startup_msg()
{
    const char *message = 
        "         _____   _                              _____   _____ \n"
        "        |_   _| (_)                            |  _  | /  ___|\n"
        "          | |    _   _ __    _   _    ______   | | | | \\ `--. \n"
        "          | |   | | | '_ \\  | | | |  |______|  | | | |  `--. \\\n"
        "          | |   | | | | | | | |_| |            \\ \\_/ / /\\__/ /\n"
        "          \\_/   |_| |_| |_|  \\__, |             \\___/  \\____/ \n"
        "                              __/ |                           \n"
        "                             |___/                            \n";
    kprint("\n\n");
    kprint(message); 
    kprint("\n\n");
}

void main() 
{   
    startup_msg();

    install_isr(); 
    asm volatile ("sti");

    init_timer(50);
    init_keyboard(); 
    init_memory_allocator(); 
}