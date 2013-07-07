#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    NOP,
    LDX_IMM,
    0xFF,
    LDA_ZP,
    0,
    STA_ZPX,
    2,
    LDY_IMM,
    0x46,
    STX_ZP,
    1,
    STY_AB,
    1,
    0,
    BRK,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
