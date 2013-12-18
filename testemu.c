#include "cpu.h"
#include "emu.h"
#include "opcodes.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("must provide input file\n");
        return -1;
    }

    FILE *in_f = fopen(argv[1], "rb");
    int b, i = 0;
    cpu *m = new_cpu();
    while ((b = fgetc(in_f)) != EOF) {
        m->mem[i++] = (uint8_t) b;
    }
    main_loop(m);
    return 0;
}
