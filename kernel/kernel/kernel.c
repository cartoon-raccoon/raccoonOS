#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/desc_tables.h>

void kernel_main(void) {
    terminal_init();
    init_desc_tables();
    printf("Welcome to RaccoonOS\n");
}