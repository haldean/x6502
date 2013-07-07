#include "debug.h"
#include "emu.h"
#include "opcodes.h"
#include <stdio.h>

static inline uint8_t mem_abs(cpu *m, uint8_t low, uint8_t high) {
    return m->mem[(uint16_t) low + ((uint16_t) high << 8)];
}

static inline void set_flags(cpu *m, uint8_t val) {
    if (val == 0) {
        m->sr |= FLAG_ZERO;
    } else {
        m->sr &= ~FLAG_ZERO;
    }

    if (val & 0x80) {
        m->sr |= FLAG_NEGATIVE;
    } else {
        m->sr &= ~FLAG_NEGATIVE;
    }
}

void main_loop(cpu *m) {
    uint32_t cycles_until_interrupt = INTERRUPT_PERIOD;
    for (;;) {
        DUMP(m);

        uint8_t opcode = NEXT_BYTE(m);
        uint8_t arg1, arg2;
        switch (opcode) {
            case BRK:
                goto end;
                break;

            case LDA_AB:
                arg1 = NEXT_BYTE(m);
                arg2 = NEXT_BYTE(m);
                m->ac = mem_abs(m, arg1, arg2);
                break;

            case LDA_IMM:
                m->ac = NEXT_BYTE(m);
                set_flags(m, m->ac);
                break;

            case LDX_IMM:
                m->x = NEXT_BYTE(m);
                set_flags(m, m->x);
                break;

            case LDY_IMM:
                m->y = NEXT_BYTE(m);
                set_flags(m, m->y);
                break;

            default:
                printf("ERROR: got unknown opcode %02x\n", opcode);
                goto end;
        }

        cycles_until_interrupt -= OPCODE_CYCLES(opcode);
        if (cycles_until_interrupt <= 0) {
            // interruption!
            cycles_until_interrupt = INTERRUPT_PERIOD;
        }
    }
end:
    return;
}
