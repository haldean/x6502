#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    LDA_IMM,    'A',
    STA_AB,     0x00, 0xFF,
    LDA_IMM,    'Z',
    INC_AB,     0x00, 0xFF,
    CMP_AB,     0x00, 0xFF,
    BNE_REL,    -6,
    LDA_IMM,    '\n',
    STA_AB,     0x00, 0xFF,
    EXT,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
