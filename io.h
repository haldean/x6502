#ifndef __6502_IO__

#include "cpu.h"

#define IO_PUTCHAR 0xFF00
#define IO_GETCHAR 0xFF01

void init_io();
void finish_io();
void handle_io(cpu *m);

#endif
