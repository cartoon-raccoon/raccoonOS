#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/serial.h>

#include "idt.h"

static idt_entry_t idt[IDT_SIZE];

struct idt_ptr idtr_desc;

extern void idt_load(struct idt_ptr *ptr);

// external isr table
extern isr isr_stub_table[EXCEPT_ISR_COUNT];

extern void int21h(void);

void int21h_handler(void)
{
    printf("Received keyboard interrupt\n");

    //acknowledge interrupt
    outb(0x20, 0x20);
}

void idt_set_entry(int interrupt, isr addr)
{
    struct idt_entry *desc = &idt[interrupt];

    desc->offset_low = (uint32_t) addr & 0x0000ffff;
    desc->selector = KERNEL_CS;
    desc->always0 = 0x00;
    desc->type_attrs = 0b11101110;
    desc->offset_hi = (uint32_t) addr >> 16;
}

void idt_init(void)
{
    memset(idt, 0x0, sizeof(idt));

    idtr_desc.limit = sizeof(idt) - 1;
    idtr_desc.base  = (uint32_t) &idt[0];

    for (int i = 0; i < EXCEPT_ISR_COUNT; i++)
    {
        idt_set_entry(i, isr_stub_table[i]);
    }

    idt_set_entry(0x21, int21h);

    idt_load(&idtr_desc);

    //enable_irqs();
}

