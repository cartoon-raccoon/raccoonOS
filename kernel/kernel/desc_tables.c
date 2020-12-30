#include <stddef.h>
#include <stdint.h>

#include <kernel/desc_tables.h>

extern void gdt_flush(uint32_t);

static void init_gdt();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
//idt_entry_t idt_entries[256];
//idt_ptr_t   idt_ptr;

void init_desc_tables() {
    init_gdt();
}

static void init_gdt() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (uint32_t) &gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                 // null segment (expected by cpu)
    gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);  // code segment
    gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);  // data segment
    gdt_set_gate(3, 0, 0xffffffff, 0xfa, 0xcf);  // user mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);  // user mode data segnent

    gdt_flush((uint32_t) &gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xffff);
    gdt_entries[num].base_middle = (base >> 16) & 0xff;

    gdt_entries[num].limit_low   = (base >> 24) & 0xff;
    gdt_entries[num].granularity = (limit >> 16) & 0x0f;

    gdt_entries[num].granularity |= gran & 0xf0;
    gdt_entries[num].access      = access;
}

