#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    LDA_IMM,
    0x80,
    INX,
    LSR_ACC,
    BNE_REL,
    0xFC,
    BRK,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
