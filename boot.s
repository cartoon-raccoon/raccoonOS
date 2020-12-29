; Declare constants for the multiboot header
MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

; Declare a multiboot header
section .multiboot
align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

; Setting aside bytes for the stack
section .bss
align 16
stack_bottom:
resb 16384 ; 16kb
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
        ; now in protected mode
        mov esp, stack_top
        extern kernel_main
        call kernel_main

        ; nothing more to do, put the system into an infinite loop
        cli
.hang:  hlt
        jmp .hang
.end: