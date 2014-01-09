case BRK:
    set_flag(m, FLAG_BREAK, 1);
    m->interrupt_waiting = 1;
    break;

case RTI:
    m->sr = STACK_POP(m);
    arg1 = STACK_POP(m);
    m->pc = mem_abs(arg1, STACK_POP(m), 0);
    break;

case WAI:
    wait_for_interrupt = 1;
    break;
