/* This file contains the interrupt service routines specific to the i686 */ 

#include <stdio.h>
#include "isr.h"

void isr_handler(registers_t regs) {
    printf("received interrupt");
}