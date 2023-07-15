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

    typedef struct  {
        uint32_t a;
        uint32_t b;
        uint8_t c;
    } BigBlob; 

    BigBlob *blob = malloc(sizeof(BigBlob));
    blob->a = 7;
    blob->b = 4096;
    blob->c = 255;

    kprint("\nblob: ");
    kprint_int(blob);
    kprint_int(blob->a);
    kprint_int(blob->b);
    kprint_int(blob->c);

    dump_heap(); 
    kprint("==========");

    BigBlob *blob2 = malloc(sizeof(BigBlob));
    blob2->a = 2;
    blob2->b = 4096;
    blob2->c = 321;

    kprint("\nblob2: ");
    kprint_int(blob2);
    kprint_int(blob2->a);
    kprint_int(blob2->b);
    kprint_int(blob2->c);
    
    // kprint("\n==========");
    
    // BigBlob *blob3 = malloc(sizeof(BigBlob));
    // blob3->a = 2;
    // blob3->b = 4096;
    // blob3->c = 321;

    // kprint("\nblob2: ");
    // kprint_int(blob2);
    // kprint_int(blob2->a);
    // kprint_int(blob2->b);
    // kprint_int(blob2->c);

}