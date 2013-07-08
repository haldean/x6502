static inline void sub(cpu *m, uint16_t r1) {
    if (get_flag(m, FLAG_DECIMAL)) {
        r1 = bcd(m->ac) - bcd(r1) - !get_flag(m, FLAG_CARRY);
        set_flag(m, FLAG_OVERFLOW, r1 > 99 || r1 < 0);
    } else {
        r1 = m->ac - r1 - !get_flag(m, FLAG_CARRY);
        set_flag(m, FLAG_OVERFLOW, 0xFF00 & r1);
    }
    set_flag(m, FLAG_CARRY, r1);
    set_flag(m, FLAG_NEGATIVE, r1 & 0x80);
    set_flag(m, FLAG_ZERO, r1 == 0);
    m->ac = r1;
}

static inline void add(cpu *m, uint16_t r1) {
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
    m->ac = r1;
}
