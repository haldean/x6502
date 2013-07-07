#include "debug.h"
#include <stdio.h>

void dump_cpu(cpu *m) {
    printf("pc %04X\nx %02X y %02X sp %02X ac %02X\n",
            m->pc, m->x, m->y, m->sp, m->ac);
    printf("n %d o %d b %d d %d i %d z %d c %d\n",
            (m->sr & FLAG_NEGATIVE) > 0,
            (m->sr & FLAG_OVERFLOW) > 0,
            (m->sr & FLAG_BREAK) > 0,
            (m->sr & FLAG_DECIMAL) > 0,
            (m->sr & FLAG_INTERRUPT) > 0,
            (m->sr & FLAG_ZERO) > 0,
            (m->sr & FLAG_CARRY) > 0);
    for (int i = 0; i < 8; i++) {
        printf("%02X ", m->mem[i]);
    }
    printf("\n\n");
}
