#include "io.h"

#include <stdio.h>
#include "functions.h"

void handle_io(cpu *m) {
    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        uint16_t dirty_addr = m->dirty_mem_addr;
        uint8_t val = m->mem[dirty_addr];

#ifdef DEBUG
        printf("dirty memory at %04x\n", dirty_addr);
#endif

        if (dirty_addr == IO_PUTCHAR) {
            putchar(val);
        }
    }
}
