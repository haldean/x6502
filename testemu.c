#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    JSR_AB,
    0x04,
    0x00,
    BRK,
    LDA_IMM,
    0xFF,
    RTS,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
