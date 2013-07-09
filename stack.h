case PHA:
    printf("%04x\n", m->sp + STACK_START);
    STACK_PUSH(m) = m->ac;
    break;

case PHP:
    STACK_PUSH(m) = m->sr;
    break;

case PLA:
    m->ac = STACK_POP(m);
    break;

case PLP:
    m->sr = STACK_POP(m);
    break;
