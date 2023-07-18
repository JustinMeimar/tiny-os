#include "types.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../libc/stdlib.h"
#include "../proc/memory.h"
#include "../proc/process.h"
#include "../drivers/screen.h"
// 
/**
 * Declare the array of GateDescriptors that constitute the IDT
 */
extern GateDescriptor idt_entries[256];
extern char _kernel_end;

static void malloc_test();
static void malloc_test2();
static void malloc_test3();

void enter_kernel() 
{   
    install_isr(); 
    asm volatile ("sti");

    init_timer(50);
    init_keyboard(); 

    clear_screen();
    // kprint("Welcome to Tiny-OS. The operating system that struggles to make your keyboard work ;)\n");
    malloc_test();
    // malloc_test2();
}

static void malloc_test()
{

    for (int i = 0; i < 100; i++)
    {
        void *ptr = malloc(128);
        free(ptr);
        
        void* ptr2 = malloc(1);
        free(ptr2);

        void* ptr3 = malloc(69);
        void* ptr4 = malloc(900);
        
        free(ptr3);
        free(ptr4);

        clear_screen();
    }

    void* ptr = malloc(128);
    void* ptr2 = malloc(128);
    void* ptr3 = malloc(128);
    void* ptr4 = malloc(128);

}
static void malloc_test3()
{
    for (int i = 0; i<1000; i++ )
    {
        void *ptr = malloc(64);

        void *ptr_1 = malloc(16);
        // memset(ptr_1, 1, 16);
        void *ptr_2 = malloc(16);
        // memset(ptr_2, 1, 16);
        free(ptr_1); 
        void *ptr_3 = malloc(16);
        // memset(ptr_3, 1, 16);
        void *ptr_4 = malloc(16);

        clear_screen();

        free(ptr);
        free(ptr_1);
        free(ptr_2);
        free(ptr_3);
        free(ptr_4);
    }
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
    // kprint_hex((uint32_t)big_space);
    
    kprint("\nblob: ");
    // kprint_int(blob->a);
    // kprint_int(blob->b);
    // kprint_int(blob->c);
 
    kprint("\nblob2: ");
    // kprint_int(blob2->a);
    // kprint_int(blob2->b);
    // kprint_int(blob2->c);
    
    kprint("\nblob3: ");
    // kprint_int(blob3->a);
    // kprint_int(blob3->b);
    // kprint_int(blob3->c);

    free(blob);
    free(blob2);
    free(big_space2);
    free(blob3);
}

// static void startup_msg()
// {
//     const char *message = 
//         "         _____   _                              _____   _____ \n"
//         "        |_   _| (_)                            |  _  | /  ___|\n"
//         "          | |    _   _ __    _   _    ______   | | | | \\ `--. \n"
//         "          | |   | | | '_ \\  | | | |  |______|  | | | |  `--. \\\n"
//         "          | |   | | | | | | | |_| |            \\ \\_/ / /\\__/ /\n"
//         "          \\_/   |_| |_| |_|  \\__, |             \\___/  \\____/ \n"
//         "                              __/ |                           \n"
//         "                             |___/                            \n";
//     kprint("\n\n");
//     kprint(message); 
//     kprint("\n\n");
// }