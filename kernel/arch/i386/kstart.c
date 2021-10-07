#include <kernel.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/log.h>

#include "gdt/gdt.h"
#include "idt/idt.h"

// todo: pass multiboot info struct to it
void kernel_init(void) 
{

    terminal_init();
    //todo: set up gdt, idt, tss, paging etc etc

    // initialize global desc table
    gdt_init();
    kernel_log("Initialized GDT\n");

    // initialize interrupt desc table
    idt_init();
    kernel_log("Initialized IDT\n");

    // call generic kernel main
    kernel_log("Calling kernel main\n");
    kernel_main();
}