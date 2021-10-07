#ifndef KERNEL_LOG_H
#define KERNEL_LOG_H

// The address of the port to write to.
#define SERIAL_PORT 0x3f8


// writes a string to COM1.
void kernel_log(char *str);

#endif