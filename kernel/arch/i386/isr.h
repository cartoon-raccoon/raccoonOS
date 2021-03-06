#ifndef _KERNEL_ISR_H
#define _KERNEL_ISR_H 1

#include <stdint.h>

typedef struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, errcode;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

#endif