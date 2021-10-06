#ifndef KSTART_H
#define KSTART_H

/* 
This is the architecture-specific entry point into the kernel.
Architecture-specific features such as the GDT, IDT, TSS, etc are initialized here.
After everything, it calls the main kernel entry point in kernel/kernel.c.
*/
void kernel_init(void);

#endif