#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

int main(int argc, char *argv[]) {
    cpu *m = new_cpu();
    int i = 0;
    m->mem[i++] = LDA_IMM;
    m->mem[i++] = 200;
    m->mem[i++] = LDA_AB;
    m->mem[i++] = 2;
    m->mem[i++] = 0;
    m->mem[i++] = BRK;
    main_loop(m);
}
