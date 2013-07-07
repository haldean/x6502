#include "debug.h"
#include <stdio.h>

void dump_cpu(cpu *m) {
    printf("PC %04x\nX %02x Y %02x SP %02x AC %02x\n",
            m->pc, m->x, m->y, m->sp, m->ac);
    printf("N %d O %d B %d D %d I %d Z %d C %d\n",
            (m->sr & FLAG_NEGATIVE) > 0,
            (m->sr & FLAG_OVERFLOW) > 0,
            (m->sr & FLAG_BREAK) > 0,
            (m->sr & FLAG_DECIMAL) > 0,
            (m->sr & FLAG_INTERRUPT) > 0,
            (m->sr & FLAG_ZERO) > 0,
            (m->sr & FLAG_CARRY) > 0);
    for (int i = 0; i < 8; i++) {
        printf("%02x ", m->mem[i]);
    }
    printf("\n\n");
}
