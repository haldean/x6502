case STA_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->mem[mem_abs(arg1, arg2, 0)] = m->ac;
    break;

case STA_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->mem[mem_abs(arg1, arg2, m->x)] = m->ac;
    break;

case STA_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->mem[mem_abs(arg1, arg2, m->y)] = m->ac;
    break;

case STA_INX:
    m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)] = m->ac;
    break;

case STA_INY:
    m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)] = m->ac;
    break;

case STA_ZP:
    m->mem[ZP(NEXT_BYTE(m))] = m->ac;
    break;

case STA_ZPX:
    m->mem[ZP(NEXT_BYTE(m) + m->x)] = m->ac;
    break;

case STX_ZP:
    m->mem[ZP(NEXT_BYTE(m))] = m->x;
    break;

case STX_ZPY:
    m->mem[ZP(NEXT_BYTE(m) + m->y)] = m->x;
    break;

case STX_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->mem[mem_abs(arg1, arg2, 0)] = m->x;
    break;

case STY_ZP:
    m->mem[ZP(NEXT_BYTE(m))] = m->y;
    break;

case STY_ZPX:
    m->mem[ZP(NEXT_BYTE(m) + m->x)] = m->y;
    break;

case STY_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->mem[mem_abs(arg1, arg2, 0)] = m->y;
    break;
