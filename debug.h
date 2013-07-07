#ifndef __6502_DEBUG__
#define __6502_DEBUG__

#include "cpu.h"

#ifdef DEBUG
#define DUMP(cpu) (dump_cpu(cpu))
#else
#define DUMP(cpu)
#endif

void dump_cpu(cpu *m);

#endif
