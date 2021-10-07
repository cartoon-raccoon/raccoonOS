#include <string.h>

#include "gdt.h"

void gdt_encode_entry(uint8_t* target, struct gdt_structured source)
{
    if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF))
    {
        //panic("encodeGdtEntry: Invalid argument\n");
        //todo: add a panic
    }

    target[6] = 0x40;
    if (source.limit > 65536)
    {
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    }

    // Encodes the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0x0F;

    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Set the type
    target[5] = source.type;

}

void gdt_structured_to_gdt(struct gdt_entry* gdt, struct gdt_structured* structured_gdt, int total_entries)
{
    for (int i = 0; i < total_entries; i++)
    {
        gdt_encode_entry((uint8_t*)&gdt[i], structured_gdt[i]);
    }
}

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

void gdt_init(void)
{
    // zero out gdt memory
    memset(gdt, 0x00, sizeof(gdt));

    // encode the gdt and load it
    gdt_structured_to_gdt(gdt, structured_gdt, TOTAL_GDT_SEGMENTS - 1);
    gdt_load(gdt, sizeof(gdt));
}