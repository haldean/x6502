#ifndef __6502_IO__

#include "cpu.h"

#define IO_PUTCHAR    0xFF00
#define IO_GETCHAR    0xFF01
#define IO_MODEFLAGS  0xFF02
#define IO_PAINT      0xFEE8

#define IO_VTERM_START 0xFB00
#define IO_VTERM_END   0xFF00

#define IO_MODEFLAG_VTERM     0x01
#define IO_MODEFLAG_WAIT_HALT 0x02

#define IO_PAINT_BLACK     0x00
#define IO_PAINT_RED       0x01
#define IO_PAINT_GREEN     0x02
#define IO_PAINT_YELLOW    0x03
#define IO_PAINT_BLUE      0x04
#define IO_PAINT_MAGENTA   0x05
#define IO_PAINT_CYAN      0x06
#define IO_PAINT_WHITE     0x07

// bitwise-OR these with one of the colors to modify them
#define IO_PAINT_DIM       0x20
#define IO_PAINT_UNDERLINE 0x40
#define IO_PAINT_BOLD      0x80

void init_io();
void finish_io();
void handle_io(cpu *m);

#endif
