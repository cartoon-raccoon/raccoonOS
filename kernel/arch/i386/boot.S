# Declare constants for the multiboot header
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Declare the multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Set up a stack
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

# The entry point
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp

    call _init

    call kernel_main
    cli
1:  hlt
    jmp 1b 
.size _start, . - _start