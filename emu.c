#include "debug.h"
#include "emu.h"
#include "opcodes.h"
#include <stdio.h>

#define ZP(x) ((uint8_t) (x))

static inline size_t mem_abs(uint8_t low, uint8_t high, uint8_t off) {
    return (uint16_t) off + (uint16_t) low + ((uint16_t) high << 8);
}

static inline size_t mem_indirect_index(cpu *m, uint8_t addr, uint8_t off) {
    return mem_abs(m->mem[addr], m->mem[addr+1], off);
}

static inline size_t mem_indexed_indirect(cpu *m, uint8_t addr, uint8_t off) {
    return mem_abs(m->mem[addr+off], m->mem[addr+off+1], 0);
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

            case NOP:
                break;

            #include "load.h"
            #include "store.h"
            #include "transfer.h"
            #include "stack.h"
            #include "logical.h"

            default:
                printf("ERROR: got unknown opcode %02x\n", opcode);
                goto end;
        }

        cycles_until_interrupt -= OPCODE_CYCLES(opcode);
        if (cycles_until_interrupt <= 0) {
            // interruption!
            cycles_until_interrupt = INTERRUPT_PERIOD;
        }

#ifdef DEBUG
        m->last_opcode = opcode;
#endif
    }
end:
    return;
}
