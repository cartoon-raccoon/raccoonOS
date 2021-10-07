#ifndef PIC_H
#define PIC_H

#include <stdint.h>

// PIC ports
#define PIC1_COM  0x20
#define PIC1_DATA 0x21
#define PIC2_COM  0xa0
#define PIC2_DATA 0xa1

/*note: ICW stands for initialization command word*/

#define ICW1_ICW4	    0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	    0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	    0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	    0x10		/* Initialization - required! */
 
#define ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	    0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	    0x10		/* Special fully nested (not) */

// New master and slave IRQ offsets
#define RM_OFFSET_1 0x20
#define RM_OFFSET_2 0x28

/* 
The PIC needs to be remapped on startup, as IDT offsets
0-14 and 16 are used by the CPU for exception trap handlers.
This conflicts with IRQs 0-7 on the master PIC.

We could perform checks (reading the mask register bit
in the PIC) to determine if an interrupt is from the PIC
or a CPU exception, but that requires extra instructions
and thus compute time.

Thus, we need to reprogram the PIC to remap IRQs 0-7 to
ISRs 0x20-0x27.
Similarly, for the slave PIC, we will remap its offsets to
ISRs 0x28-0x2f.

So, when IRQ line 1 is raised (keyboard PS/2 interrupt),
instead of calling ISR1 (which is reserved for debug
exceptions), we will call ISR 0x20+1 = 0x21.
*/

// Remap the PIC's IRQ lines to the given offsets.
void pic_remap(uint8_t offset1, uint8_t offset2);

// Sets the corresponding bit in the IRQ mask register.
// When the bit is set, the IRQ is ignored when the pin
// is raised and the CPU does not receive interrupts.
void pic_set_irq_mask(uint8_t irqline);

// Clears the corresponding bit in the IRQ mask register.
// Similarly, when the bit is clear, IRQs will be received
// by the CPU again.
void pic_clr_irq_mask(uint8_t irqline);

#endif