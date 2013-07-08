#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

uint8_t prog[] = {
    LDA_IMM,
    0x01,
    STA_ZP,
    0x0F,
    LDA_IMM,
    0xFF,
    ADC_ZP,
    0x0F,
    ADC_IMM,
    0xF0,
    BRK,
};

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    for (int i = 0; i < sizeof(prog); i++) {
        m->mem[i] = prog[i];
    }
    main_loop(m);
}
