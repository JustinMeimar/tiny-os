#ifndef PROCESS_H
#define PROCESS_H

#include "../kernel/types.h"
#include "../cpu/timer.h"
#include "memory.h"

typedef struct ProcessControlBlock ProcessControlBlock;
typedef struct Process Process;

typedef struct {
   uint32_t ds; /* Data segment selector */
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
   uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} RegistersTy;

/**
 * Struct to hold ready processes. A process is ready when
 * there is ready work to be done.  
 */
typedef struct 
{
    uint32_t id;
} ProcessReadyQueue;

/**
 * Struct to hold waiting processes. A process can be waiting because has 
 * performed some I/O operation and is waiting for a return. 
 */
typedef struct 
{
    uint32_t id;
} ProcessWaitQueue;

// Process State
typedef enum 
{
    START,
    READY, 
    WAIT,
    TERMINATE
} ProcessState;

// PCB
struct ProcessControlBlock
{
    uint32_t pid;
    Process *process;
    ProcessControlBlock *parent;
    ProcessControlBlock *children;
    uint8_t child_cnt;
    ProcessState state;
    uint8_t exit_status;
};

// The actual process
struct Process
{
    void *stack;
    void *heap;
    void *text;
    void *data;
};

void init_system_d();

#endif