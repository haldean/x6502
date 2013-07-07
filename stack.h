case PHA:
    printf("%04x\n", m->sp + STACK_START);
    m->mem[m->sp-- + STACK_START] = m->ac;
    break;

case PHP:
    m->mem[m->sp-- + STACK_START] = m->sr;
    break;

case PLA:
    m->ac = m->mem[++m->sp + STACK_START];
    break;

case PLP:
    m->sr = m->mem[++m->sp + STACK_START];
    break;
