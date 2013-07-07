case ADC_IMM:
    r1 = NEXT_BYTE(m);
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
    m->ac = 0xFF & r1;
    break;
