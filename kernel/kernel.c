#include <stdio.h>
#include <kernel/tty.h>
//#include <kernel/desc_tables.h>

void kernel_main(void) {
    terminal_init();
    //init_desc_tables();
    printf("Welcome to RaccoonOS\n");
    printf("\n");
    //asm volatile ("int $0x3");
    //asm volatile ("int $0x4");
}