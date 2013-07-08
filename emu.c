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

// set arg MUST be 16 bits, not 8, so that add results can fit into set.
static inline void set_flag(cpu *m, uint8_t flag, uint16_t set) {
    if (set) {
        m->sr |= flag;
    } else {
        m->sr &= ~flag;
    }
}

static inline uint8_t get_flag(cpu *m, uint8_t flag) {
    return (m->sr & flag) > 0;
}

static inline void set_flags(cpu *m, uint8_t val) {
    set_flag(m, FLAG_ZERO, !val);
    set_flag(m, FLAG_NEGATIVE, val & 0x80);
}

static inline uint8_t bcd(uint8_t val) {
    // bcd is "binary coded decimal"; it treats the upper nibble and lower
    // nibble of a byte each as a decimal digit, so 01011000 -> 0101 1000 -> 58.
    // in other words, treat hex output as decimal output, so 0x58 is treated as
    // 58. this is dumb and adds a bunch of branching to opcode interpretation
    // that I Do Not Like.
    return 10 * (val >> 4) + (0x0F & val);
}

#include "functions.h"

void main_loop(cpu *m) {
    uint32_t cycles_until_interrupt = INTERRUPT_PERIOD;

    uint8_t opcode;
    uint8_t arg1, arg2, t1;
    uint16_t r1;

    for (;;) {
        DUMP(m);

        opcode = NEXT_BYTE(m);
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
            #include "arithmetic.h"

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
