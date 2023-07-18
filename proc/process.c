#include "process.h"

#define MAX_PROCESSES 20

// The process will be 4K
#define HEAP_SIZE 1024
#define STACK_SIZE 1024
#define TEXT_SIZE 1024
#define DATA_SIZE 1024

ProcessControlBlock *pbc_buffers;
uint32_t current_process = 0;

static void init_process_control()
{
    pbc_buffers = malloc(MAX_PROCESSES * sizeof(ProcessControlBlock));
}

void init_system_d()
{
    init_process_control(); 
    
    Process *system_d = malloc(sizeof(Process));
    system_d->stack = malloc(STACK_SIZE);
    system_d->heap = malloc(HEAP_SIZE);
    system_d->text = malloc(TEXT_SIZE);
    system_d->data = malloc(DATA_SIZE);

    // ProcessControlBlock *system_d_pcb = &pbc_buffers[0];
    // system_d_pcb.pid = 1;   
    // system_d_pcb.process = system_d;
    // system_d_pcb.state = READY;
    
    // while(system_d_pcb.state != TERMINATE){
    //     //loop
    //     sleep(1000);
    //     kprint("---system_d\n");
    //     continue;
    // }
}

// void pause_process(uint32_t pid)
// {
//     // __asm__(); //push registers
// }

// void resume_process(uint32_t pid)
// {

// }

// void context_switch(uint32_t old_process, uint32_t new_process)
// {
//     pause_process(old_process);
//     current_process = new_process;
//     resume_process(new_process);
// }

