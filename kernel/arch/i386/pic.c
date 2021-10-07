#include <kernel/serial.h>
#include <stdint.h>

#include "pic.h"

void pic_remap(uint8_t offset1, uint8_t offset2)
{
    uint8_t mr_pic1, mr_pic2; // PIC mask registers

    mr_pic1 = inb(PIC1_DATA);
    mr_pic2 = inb(PIC2_DATA);

    outb(PIC1_COM, ICW1_INIT | ICW1_ICW4); // start init sequence
    io_wait();
    outb(PIC2_COM, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1);  // PIC1 vector offset
    io_wait();
    outb(PIC2_DATA, offset2);  // PIC2 vector offset
    io_wait();
    outb(PIC1_DATA, 4);        // tell master PIC of slave PIC
    io_wait();
    outb(PIC2_DATA, 2);        // tell slave its cascade identity
    io_wait();
    
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // restore saved masks
    outb(PIC1_DATA, mr_pic1);
    outb(PIC2_DATA, mr_pic2);
}