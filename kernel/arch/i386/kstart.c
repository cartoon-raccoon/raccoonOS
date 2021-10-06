#include <kernel.h>
#include <string.h>

#include "gdt/gdt.h"

//! Remove the -1 from TOTAL_GDT_SEGMENTS - 1 after adding tss
struct gdt_structured structured_gdt[TOTAL_GDT_SEGMENTS - 1] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                // NULL Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},            // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},             // User data segment
    //{.base = (uint32_t)&tss, .limit=sizeof(tss), .type = 0xE9}      // TSS Segment
};

struct gdt_entry gdt[TOTAL_GDT_SEGMENTS - 1];

// todo: pass multiboot info struct to it
void kernel_init(void) {
    //todo: set up gdt, idt, etc etc

    // zero out gdt memory
    memset(gdt, 0x00, sizeof(gdt));

    // encode the gdt and load it
    gdt_structured_to_gdt(gdt, structured_gdt, TOTAL_GDT_SEGMENTS - 1);
    gdt_load(gdt, sizeof(gdt));

    // call generic kernel main
    kernel_main();
}