#include <stdio.h>
#include <kernel/tty.h>

void kernel_main(void) {
    terminal_init();
    printf("Welcome to RaccoonOS\n");
    printf("\n");

    for (;;);
}