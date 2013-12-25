#ifndef __6502_IO__

#include "cpu.h"

#define IO_PUTCHAR      0xFF00
#define IO_GETCHAR      0xFF01

// return values for handle_io
#define IO_OK           0
#define IO_HALT         1

void init_io();
void finish_io();
int handle_io(cpu *m);

#endif
