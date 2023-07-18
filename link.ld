SECTIONS
{
    . = 0x1000;
    .text : { *(.text)}
    .data : { *(.data)}
    .bss  : { *(.bss)}
    . = 0x90000; 
    _kernel_end = .;
}