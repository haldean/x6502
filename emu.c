#include "emu.h"

#include <stdio.h>
#include "debug.h"
#include "functions.h"
#include "opcodes.h"

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
            #include "compare.h"
            #include "incdec.h"

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
