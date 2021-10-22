/* This file contains the interrupt service routines specific to the i686 */ 

#include <stdio.h>
#include <kernel/log.h>
#include "isr.h"

void isr_handler(char intr, char errcode) {

    if (errcode) 
    {
        printf("Received error interrupt\n");
    }

    char code;
    switch (intr)
    {
        case 0:
            code = 'z';
            break;
        case 1:
            code = '1';
            break;
        case 2:
            code = '2';
            break;
        case 0x21:
            code = 'k';
            break;
        default:
            code = 'o';
            break;
    }

    kernel_log("Received interrupt %c\n");
    printf("Received interrupt %c\n", code);
}