case JMP_AB:
    arg1 = NEXT_BYTE(m);
    m->pc = mem_abs(arg1, NEXT_BYTE(m), 0);
    break;

case JMP_IN:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    m->pc = mem_abs(m->mem[r1], m->mem[r1+1], 0);
    break;

case JSR_AB:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    r2 = m->pc - 1;
    STACK_PUSH(m) = (r2 & 0xFF00) >> 8;
    STACK_PUSH(m) = r2 & 0xFF;
    m->pc = r1;
    break;

case RTS:
    arg1 = STACK_POP(m);
    m->pc = mem_abs(arg1, STACK_POP(m), 0) + 1;
    break;

case BRK:
    // this can't use the normal interrupt logic because the break flag needs to
    // be set
    m->pc++;
    STACK_PUSH(m) = (m->pc & 0xFF00) >> 8;
    STACK_PUSH(m) = m->pc & 0xFF;
    STACK_PUSH(m) = m->sr | FLAG_BREAK;
    m->pc = mem_abs(m->mem[0xFFFE], m->mem[0xFFFF], 0);
    m->sr |= FLAG_INTERRUPT;
    break;

case RTI:
    m->sr = STACK_POP(m);
    arg1 = STACK_POP(m);
    m->pc = mem_abs(arg1, STACK_POP(m), 0);
    break;
