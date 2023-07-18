#include "types.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/display.h"
#include "../libc/stdlib.h"
#include "../proc/memory.h"
#include "../proc/process.h"
#include "../tests/tests.h"

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

static void malloc_test();

void enter_kernel() 
{   
    startup_msg();
    install_isr(); 
    asm volatile ("sti");

    init_timer(50);
    init_keyboard(); 

    if (test_prints() == 1) {
        kprint("tests returned 1\n");
    } else {
        kprint("tests returned 0\n");
    }
    // malloc_test();

    // init_system_d();
}

static void malloc_test()
{

    // for (int i = 0; i < 1; i++) {
    //     kprint("malloc 64k: "); 
    //     kprint_hex(i);
    //     kprint("\n");

    //     void *ptr = malloc(64000);
    //     free(ptr);
    // }

    void *ptr_1 = malloc(16);
    // memset(ptr_1, 1, 16);
    void *ptr_2 = malloc(16);
    // memset(ptr_2, 1, 16);
    free(ptr_1); 
    void *ptr_3 = malloc(16);
    // memset(ptr_3, 1, 16);
    void *ptr_4 = malloc(16);


    // for (uint32_t i = 0; i < 10; i++) {
    //     void *recycle_me = malloc(16);
    //     // memset(recycle_me, 69, 1024);
    //     // memset(recycle_me, 1, 16);
    //     free(recycle_me);
    // }
    // kprint_hex((uint32_t)&_kernel_end);
    // while(1)
    // {
    //     kprint("testing malloc\n");
    //     void *ptr = malloc(8);
    //     sleep(100);
    // }
}

static void malloc_test2()
{
    typedef struct  {
        uint32_t a;
        uint16_t b;
        uint8_t c;
    } BigBlob; 

    BigBlob *blob = malloc(sizeof(BigBlob));
    blob->a = 7;
    blob->b = 4096;
    blob->c = 255;
    
    void *big_space = malloc(64);
    
    BigBlob *blob2 = malloc(sizeof(BigBlob));
    blob2->a = 2;
    blob2->b = 4096;
    blob2->c = 255;
    
    void *big_space2 = malloc(72);
    
    free(big_space);

    BigBlob *blob3 = malloc(sizeof(BigBlob));
    blob3->a = 7;
    blob3->b = 8;
    blob3->c = 9;

    kprint("big space:");
    kprint_hex((uint32_t)big_space);
    
    kprint("\nblob: ");
    kprint_int(blob->a);
    kprint_int(blob->b);
    kprint_int(blob->c);
 
    kprint("\nblob2: ");
    kprint_int(blob2->a);
    kprint_int(blob2->b);
    kprint_int(blob2->c);
    
    kprint("\nblob3: ");
    kprint_int(blob3->a);
    kprint_int(blob3->b);
    kprint_int(blob3->c);

    free(blob);
    free(blob2);
    free(big_space2);
    free(blob3);
}