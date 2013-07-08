case INC_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flags(m, ++m->mem[mem_abs(arg1, arg2, 0)]);
    break;

case INC_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flags(m, ++m->mem[mem_abs(arg1, arg2, m->x)]);
    break;

case INC_ZP:
    set_flags(m, ++m->mem[NEXT_BYTE(m)]);
    break;

case INC_ZPX:
    set_flags(m, ++m->mem[ZP(NEXT_BYTE(m) + m->x)]);
    break;

case INX:
    set_flags(m, ++m->x);
    break;

case INY:
    set_flags(m, ++m->y);
    break;

case DEC_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flags(m, --m->mem[mem_abs(arg1, arg2, 0)]);
    break;

case DEC_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    set_flags(m, --m->mem[mem_abs(arg1, arg2, m->x)]);
    break;

case DEC_ZP:
    set_flags(m, --m->mem[NEXT_BYTE(m)]);
    break;

case DEC_ZPX:
    set_flags(m, --m->mem[ZP(NEXT_BYTE(m) + m->x)]);
    break;

case DEX:
    set_flags(m, --m->x);
    break;

case DEY:
    set_flags(m, --m->y);
    break;
