ALIGNMENT equ 1<<0
MEMINFO   equ 1<<1
FLAGS     equ ALIGNMENT | MEMINFO
MAGIC     equ 1badb002h
CHECKSUM  equ -(MAGIC + FLAGS)
 
section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM
 
section .bss
align 16
stack_bottom:
resb 16384
stack_top:
 
[bits 32]
section .text
global _start
 
extern _init
extern kernel_init
 
_start:
    cli
    mov esp, stack_top
 
    call _init
 
    call kernel_init
    cli
.1: hlt
    jmp .1