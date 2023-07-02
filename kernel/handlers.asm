; extern C function in your kernel that will handle the IRQs
extern handle_irq

; declare IRQ handlers as global
global irq0
global irq1
global irq2
global irq3

; IRQ handler definitions
irq0:
    pusha 
    push byte 0 ;// dummy error state
    push byte 0 ; IRQ number
    jmp irq_common

irq1:
    pusha 
    push dword 0 ;// dummy error state 
    push dword 1 ; IRQ number
    jmp irq_common

irq2:
    pusha 
    push dword 0 ;// dummy error state 
    push dword 2 ; IRQ number
    jmp irq_common

irq3:
    pusha 
    push dword 0 ; // dummy error state
    push dword 3 ; IRQ number
    jmp irq_common

; common IRQ handler code
irq_common: 
    cld
    mov eax, dword [esp] ;save the IRQ number 
    mov ecx, eax ;pass IRQ as arg to handle_irq
    call handle_irq  
    add esp, 8 ;// pop the two byte pushes
    popa 
    iret
