#ifndef __6502_DEBUG__
#define __6502_DEBUG__

#include "cpu.h"

#ifdef DEBUG
#define DUMP_DEBUG(cpu) (dump_cpu(cpu))
#else
#define DUMP_DEBUG(cpu)
#endif

void dump_cpu(cpu *m);

#endif
