case ADC_AB:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    r1 = m->mem[mem_abs(arg1, arg2, 0)];
    goto add_impl;

case ADC_ABX:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    r1 = m->mem[mem_abs(arg1, arg2, m->x)];
    goto add_impl;

case ADC_ABY:
    arg1 = NEXT_BYTE(m);
    arg2 = NEXT_BYTE(m);
    r1 = m->mem[mem_abs(arg1, arg2, m->y)];
    goto add_impl;

case ADC_IMM:
    r1 = NEXT_BYTE(m);
    goto add_impl;

case ADC_INX:
    r1 = m->mem[mem_indexed_indirect(m, NEXT_BYTE(m), m->x)];
    goto add_impl;

case ADC_INY:
    r1 = m->mem[mem_indirect_index(m, NEXT_BYTE(m), m->y)];
    goto add_impl;

case ADC_ZP:
    r1 = m->mem[NEXT_BYTE(m)];
    goto add_impl;

case ADC_ZPX:
    r1 = m->mem[ZP(NEXT_BYTE(m) + m->x)];
    goto add_impl;

add_impl:
    // committing a cardinal sin for my sanity's sake. callers should initialize
    // r1 to the argument to the add.
    if (get_flag(m, FLAG_DECIMAL)) {
        r1 = bcd(r1) + bcd(m->ac) + get_flag(m, FLAG_CARRY);
        set_flag(m, FLAG_CARRY, r1 > 99);
    } else {
        r1 += m->ac + get_flag(m, FLAG_CARRY);
        set_flag(m, FLAG_CARRY, r1 & 0xFF00);
    }
    set_flag(m, FLAG_OVERFLOW, (m->ac & 0x80) != (r1 & 0x80));
    set_flag(m, FLAG_ZERO, r1 == 0);
    set_flag(m, FLAG_NEGATIVE, r1 & 0x80);
    m->ac = 0xFF & r1;
    break;
