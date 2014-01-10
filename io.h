#ifndef __6502_IO__

#include "cpu.h"

#define IO_PUTCHAR    0xFF00
#define IO_GETCHAR    0xFF01
#define IO_MODEFLAGS  0xFF02

#define IO_VTERM_START 0xFB00
#define IO_VTERM_END   0xFF00

#define IO_MODEFLAG_VTERM     0x01
#define IO_MODEFLAG_WAIT_HALT 0x02

void init_io();
void finish_io();
void handle_io(cpu *m);

#endif
