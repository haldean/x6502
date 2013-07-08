#ifndef __6502_EMU__
#define __6502_EMU__

#include "cpu.h"

#define ZP(x) ((uint8_t) (x))

void main_loop(cpu *m);

#endif
