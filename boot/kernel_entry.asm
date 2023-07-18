[bits 32]
[extern enter_kernel] ; Define calling point. Must have same name as kernel.c 'main' function
call enter_kernel ; Calls the C function. The linker will know where it is placed in memory
jmp $
