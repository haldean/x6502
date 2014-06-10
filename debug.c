#include "debug.h"
#include "debug-names.h"
#include <stdio.h>

#define MEM_PRINT_BYTES 16
#define MAX_MEM_OFFSET (MEMORY_SIZE - MEM_PRINT_BYTES)

void dump_cpu(cpu *m) {
    return;
    init_names();

    int i;
    printf("pc %04X\nx %02X y %02X sp %02X sr %02X ac %02X",
            m->pc, m->x, m->y, m->sp, m->sr, m->ac);

    printf("\nlast opcode: %s (%02X)",
            inst_names[m->last_opcode], m->last_opcode);
    printf(", next opcode: %s (%02X)",
            inst_names[m->mem[m->pc]], m->mem[m->pc]);

    printf("\nflags n %d o %d b %d d %d i %d z %d c %d",
            (m->sr & FLAG_NEGATIVE) > 0,
            (m->sr & FLAG_OVERFLOW) > 0,
            (m->sr & FLAG_BREAK) > 0,
            (m->sr & FLAG_DECIMAL) > 0,
            (m->sr & FLAG_INTERRUPT) > 0,
            (m->sr & FLAG_ZERO) > 0,
            (m->sr & FLAG_CARRY) > 0);

    printf("\nmem   ");

    int mem_offset = m->pc - MEM_PRINT_BYTES / 2;
    // clamp to [0, MAX_MEM_OFFSET]
    mem_offset = mem_offset < 0 ? 0 : (
            mem_offset > MAX_MEM_OFFSET ? MAX_MEM_OFFSET : mem_offset);

    for (i = 0; i < MEM_PRINT_BYTES; i++) {
        printf("%02X ", m->mem[i + mem_offset]);
    }

    printf("\n      ");
    for (i = 0; i < m->pc - mem_offset; i++) {
        printf("   ");
    }
    printf("^^ (%04x)", m->pc);

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
