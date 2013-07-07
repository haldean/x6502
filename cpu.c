#include "cpu.h"
#include <stdlib.h>
#include <string.h>

cpu * new_cpu() {
    cpu *m = malloc(sizeof(cpu));
    m->pc = 0;
    m->sr = 0;
    memset(m->mem, 0xFF, MEMORY_SIZE);
    return m;
}
