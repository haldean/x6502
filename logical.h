case AND_IMM:
    m->ac &= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case AND_ZP:
    m->ac &= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case AND_ZPX:
    m->ac &= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case AND_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case AND_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case AND_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac &= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case AND_INX:
    m->ac &= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case AND_INY:
    m->ac &= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;

case EOR_IMM:
    m->ac ^= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case EOR_ZP:
    m->ac ^= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case EOR_ZPX:
    m->ac ^= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case EOR_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case EOR_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case EOR_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac ^= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case EOR_INX:
    m->ac ^= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case EOR_INY:
    m->ac ^= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;

case ORA_IMM:
    m->ac |= NEXT_BYTE(m);
    set_flags(m, m->ac);
    break;

case ORA_ZP:
    m->ac |= m->mem[NEXT_BYTE(m)];
    set_flags(m, m->ac);
    break;

case ORA_ZPX:
    m->ac |= m->mem[ZP(NEXT_BYTE(m) + m->x)];
    set_flags(m, m->ac);
    break;

case ORA_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, 0)];
    set_flags(m, m->ac);
    break;

case ORA_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, m->x)];
    set_flags(m, m->ac);
    break;

case ORA_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    m->ac |= m->mem[mem_abs(arg1, arg2, m->y)];
    set_flags(m, m->ac);
    break;

case ORA_INX:
    m->ac |= m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    set_flags(m, m->ac);
    break;

case ORA_INY:
    m->ac |= m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    set_flags(m, m->ac);
    break;
