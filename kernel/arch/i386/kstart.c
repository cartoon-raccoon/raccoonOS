#include <kernel.h>

// todo: pass multiboot info struct to it
void kernel_init(void) {
    // set up gdt, idt, etc etc

    // call generic kernel main
    kernel_main();
}