#include "cpu.h"
#include <stdlib.h>
#include <string.h>

cpu * new_cpu() {
    cpu *m = malloc(sizeof(cpu));
    m->pc = 0x00;
    m->sr = FLAG_INTERRUPT;
    m->sp = 0xFF;
    m->interrupt_waiting = 0x00;
    memset(m->mem, 0xFF, MEMORY_SIZE);
    return m;
}
