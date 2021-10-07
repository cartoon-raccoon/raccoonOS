#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "idt.h"

static idt_entry_t idt[IDT_SIZE];

struct idt_ptr idtr_desc;

extern void idt_load(struct idt_ptr *ptr);

static void idt_zero();
static void idt_zero() {
    printf("Divide by zero!\n");
    asm volatile("pop %eax");
    //asm volatile("hlt");
}

void idt_set(int interrupt, void *addr) {
    struct idt_entry *desc = &idt[interrupt];

    desc->offset_low = (uint32_t) addr & 0x0000ffff;
    desc->selector = KERNEL_CS;
    desc->always0 = 0x00;
    desc->type_attrs = 0b11101110;
    desc->offset_hi = (uint32_t) addr >> 16;
}

void idt_init(void) {
    memset(idt, 0x0, sizeof(idt));

    idtr_desc.limit = sizeof(idt) - 1;
    idtr_desc.base  = (uint32_t) &idt[0];

    idt_set(0, idt_zero);

    idt_load(&idtr_desc);
}

