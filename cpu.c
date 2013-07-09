#include "cpu.h"
#include <stdlib.h>
#include <string.h>

cpu * new_cpu() {
    cpu *m = malloc(sizeof(cpu));
    m->pc = 0x00;
    m->sr = FLAG_INTERRUPT;
    m->sp = 0xFF;
    memset(m->mem, 0xFF, MEMORY_SIZE);
    return m;
}
