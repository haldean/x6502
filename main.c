#include "cpu.h"
#include "emu.h"
#include "functions.h"
#include "io.h"
#include "opcodes.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage() {
    printf("x6502: a simple 6502 emulator\n");
    printf("usage: x6502 [OPTION]... [FILE] \n");
    printf("options:\n");
    printf("\t-b addr\t\tthe base address at which code will be loaded\n");
    printf("\t-d file\t\ta binary file to back the block device\n");
    printf("\t\t\t(optional, defaults to zero)\n");
}

int main(int argc, char *argv[]) {
    int base_addr = 0x1000;
    char *blck0_file = NULL;

    int c;
    while ((c = getopt(argc, argv, "hb:d:")) != -1) {
        switch (c) {
        case 'b':
            base_addr = atoi(optarg);
            break;

        case 'd':
            blck0_file = optarg;
            break;

        case 'h':
            usage();
            return 0;

        case '?':
            if (optopt == 'b' || optopt == 'd') {
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            }
            usage();
            return -1;
        }
    }

    if (optind == argc) {
        printf("no input file specified.\n");
        usage();
        return -1;
    }

    debugf("using %s as a backing file for block device 0\n", blck0_file);
    if (blck0_file != NULL) {
        FILE *blck0 = fopen(blck0_file, "r+");
        if (blck0 == NULL) {
            fprintf(stderr, "block file %s does not exist.\n", blck0_file);
            return -1;
        }
        set_block_source(blck0);
    }

    FILE *in_f = fopen(argv[optind], "r");
    int b;
    int i = base_addr;
    cpu *m = new_cpu(base_addr);
    while ((b = fgetc(in_f)) != EOF) {
        m->mem[i++] = (uint8_t) b;
    }
    main_loop(m);
    return 0;
}
