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

void init_desc_tables();

#endif