#ifndef _KERNEL_DESC_TABLES
#define _KERNEL_DESC_TABLES

#include <stddef.h>
#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
}__attribute__((packed));

/*
Access byte format:

 7|6 5|4 |3  0
|P|DPL|DT|Type|

P: Present? 1 : 0
DPL: Descriptor privilege level (Ring) 0-3
DT: Descriptor type
Type: Segment type: Data or code


*/

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

typedef struct gdt_entry gdt_entry_t;
typedef struct gdt_ptr gdt_ptr_t;

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
}__attribute__((packed));

struct idt_ptr {
    uint16_t base;
    uint32_t limit;
}__attribute__((packed));

typedef struct idt_entry idt_entry_t;
typedef struct idt_ptr   idt_ptr_t;

void init_desc_tables();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif