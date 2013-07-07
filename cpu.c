#include "cpu.h"
#include <stdlib.h>

cpu * new_cpu() {
    cpu *m = malloc(sizeof(cpu));
    m->pc = 0;
    m->sr = 0;
    return m;
}
