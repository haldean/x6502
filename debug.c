#include "debug.h"
#include <stdio.h>

#define MEM_PRINT_BYTES 16

void dump_cpu(cpu *m) {
    int i;
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
    printf("mem   ");
    for (i = 0; i < MEM_PRINT_BYTES; i++) {
        printf("%02X ", m->mem[i]);
    }
    printf("\nstack ");
    for (i = 0; i < MEM_PRINT_BYTES; i++) {
        printf("%02X ", m->mem[STACK_START + 0xFF - i]);
    }

    int off = 0xFF - m->sp;
    if (off < MEM_PRINT_BYTES) {
        printf("\n      ");
        for (i = 0; i < off; i++) {
            printf("   ");
        }
        printf("^^");
    }
    printf("\n\n");
}
