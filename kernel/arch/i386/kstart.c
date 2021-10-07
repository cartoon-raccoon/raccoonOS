#include <kernel.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/log.h>

#include "gdt/gdt.h"
#include "idt/idt.h"
#include "pic.h"

// todo: pass multiboot info struct to it
void kernel_init(void) 
{
    // remap IRQs to ISR 0x20 onwards
    pic_remap(RM_OFFSET_1, RM_OFFSET_2);
    kernel_log("Remapped PIC\n");

    // initialize global desc table
    gdt_init();
    kernel_log("Initialized GDT\n");

    // initialize interrupt desc table
    idt_init();
    kernel_log("Initialized IDT\n");

    terminal_init();
    // call generic kernel main
    kernel_log("Calling kernel main\n");
    kernel_main();
}