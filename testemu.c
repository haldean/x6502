#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    LDX_IMM,
    0x80,
    LDY_IMM,
    0x00,
    LDA_IMM,
    0x11,
    TXA,
    TXS,
    TYA,
    BRK,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
