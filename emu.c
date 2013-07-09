#include "emu.h"

#include <stdio.h>
#include "debug.h"
#include "functions.h"
#include "opcodes.h"

void main_loop(cpu *m) {
    uint32_t cycles_until_interrupt = INTERRUPT_PERIOD;

    uint8_t opcode;
    uint8_t arg1, arg2, t1;
    int8_t s1;
    uint16_t r1, r2;

    for (;;) {
        DUMP(m);

        opcode = NEXT_BYTE(m);
        switch (opcode) {
            case NOP:
                break;

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
