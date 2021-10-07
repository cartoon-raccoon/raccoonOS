#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/vga.h>

// #if defined(__linux__)
// #error "i686 cross compiler not being used"
// #endif

// #if !defined(__i686__)
// #error "i686 not defined"
// #endif

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint8_t terminal_color;
static size_t cursor_x;
static size_t cursor_y;
static uint16_t *terminal_buffer = (uint16_t*) 0xb8000;

// initializes the terminal.
// the first function called when the kernel starts up.
void terminal_init(void)
{
    // initialize variables
    cursor_x = 0;
    cursor_y = 0;
    terminal_color = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);

    // fill the terminal buffer with spaces
    for (size_t y = 0; y < VGA_HEIGHT; y++) 
    {
        for (size_t x = 0; x < VGA_WIDTH; x++) 
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_move_cursor()
{
    uint16_t cursor = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursor >> 8);         // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursor);              // Send the low cursor byte.
}

// scrolls the terminal by one line.
void terminal_scroll()
{
    uint8_t attribute = vga_entry_color(VGA_LIGHT_GREY, VGA_BLACK);
    uint16_t blank = 0x20 | (attribute << 8);
    
    if(cursor_y >= 25) 
    {
        int i;
        for (i = 0*80; i < 24*80; i++) {
            terminal_buffer[i] = terminal_buffer[i + 80];
        }

        for (i = 24*80; i < 25*80; i++ ) {
            terminal_buffer[i] = blank;
        }

        cursor_y = 24;
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

// puts a character at the specified location.
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t idx = y * VGA_WIDTH + x;
    terminal_buffer[idx] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    if (c == 0x08 && cursor_x) 
        cursor_x--;
    else if (c == '\r')
        cursor_x = 0;
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ')
    {
        // put the char
        terminal_putentryat(c, terminal_color, cursor_x, cursor_y);

        // move the cursor
        if (++cursor_x == VGA_WIDTH) 
        {
            cursor_x = 0;
            if (++cursor_y == VGA_HEIGHT) 
                cursor_y = 0;
        }
    }

    // scroll if needed
    terminal_scroll();
    // move the cursor
    terminal_move_cursor();
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        terminal_putchar(data[i]);
    }
}

void terminal_writestr(const char* data)
{
    terminal_write(data, strlen(data));
}
