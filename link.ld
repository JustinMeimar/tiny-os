SECTIONS
{
    . = 0x1000;
    .text : { *(.text)}
    .data : { *(.data)}
    .bss  : { *(.bss)}
    . = ALIGN(4096); 
    _kernel_end = .;
}