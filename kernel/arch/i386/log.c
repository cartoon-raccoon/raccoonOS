#include <kernel/log.h>
#include <kernel/serial.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

static void kernel_log_writechar(const char c)
{
    outb(SERIAL_PORT, c);
}

static void kernel_log_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        kernel_log_writechar(data[i]);
    }
}

void kernel_log(char *str)
{
    kernel_log_write(str, strlen(str));
}