#include "emu.h"

#include <stdio.h>
#include "debug.h"
#include "functions.h"
#include "io.h"
#include "opcodes.h"

#define NEXT_BYTE(cpu) ((cpu)->mem[(cpu)->pc + (pc_offset++)])

void main_loop(cpu *m) {
    uint8_t opcode;
    uint8_t arg1, arg2, t1;
    int8_t s1;
    uint16_t r1, r2;

    // pc_offset is used to read from memory like a stream when processing
    // bytecode without modifying the pc. pc_start is the memory address of the
    // currently-executing opcode; if pc == pc_start at the end of a simulation
    // step, we add pc_offset to get the start of the next instruction. if pc !=
    // pc_start, we branched so we don't touch the pc.
    uint8_t pc_offset = 0;
    uint16_t pc_start;

    // branch_offset is an offset that will be added to the program counter
    // after we move to the next instruction
    int8_t branch_offset = 0;

    init_io();

    for (;;) {
        DUMP_DEBUG(m);

        reset_emu_flags(m);

        pc_offset = 0;
        branch_offset = 0;
        pc_start = m->pc;
        opcode = NEXT_BYTE(m);

        switch (opcode) {
            case NOP:
                break;

#ifndef DISABLE_EXTENSIONS
            case EXT:
                goto end;

            case DUMP:
                dump_cpu(m);
                break;
#endif

            #include "arithmetic.h"
            #include "branch.h"
            #include "compare.h"
            #include "flags.h"
            #include "incdec.h"
            #include "jump.h"
            #include "load.h"
            #include "logical.h"
            #include "shift.h"
            #include "stack.h"
            #include "store.h"
            #include "transfer.h"

            default:
                printf("ERROR: got unknown opcode %02x\n", opcode);
                goto end;
        }

        if (m->pc == pc_start) {
            m->pc += pc_offset;
        }
        m->pc += branch_offset;

        handle_io(m);

        if (m->interrupt_waiting && !get_flag(m, FLAG_INTERRUPT)) {
            STACK_PUSH(m) = (m->pc & 0xFF00) >> 8;
            STACK_PUSH(m) = m->pc & 0xFF;
            STACK_PUSH(m) = m->sr;

            m->interrupt_waiting = 0x00;
            m->pc = mem_abs(m->mem[0xFFFE], m->mem[0xFFFF], 0);
            m->sr |= FLAG_INTERRUPT;
        }

        m->last_opcode = opcode;
    }
end:
    finish_io();
}
