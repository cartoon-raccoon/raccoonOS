#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_SIZE 256

#define EXCEPT_ISR_COUNT 32

#define KERNEL_CS 0x08
#define KERNEL_DS 0x10

struct idt_entry 
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  always0;
    uint8_t  type_attrs;
    uint16_t offset_hi;
} __attribute__((packed));

struct idt_ptr 
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;
typedef struct idt_ptr   idt_ptr_t;

// isr function pointer
typedef void (*isr)(void);

void idt_init(void);
void idt_set_entry(int interrupt, isr addr);

void enable_irqs(void);
void disable_irqs(void);

#endif