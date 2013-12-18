case ASL_AB:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    set_flag(m, FLAG_CARRY, m->mem[r1] & 0x80);
    m->mem[r1] = (m->mem[r1] << 1) & 0xFE;
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ASL_ABX:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), m->x);
    set_flag(m, FLAG_CARRY, m->mem[r1] & 0x80);
    m->mem[r1] = (m->mem[r1] << 1) & 0xFE;
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ASL_ACC:
    set_flag(m, FLAG_CARRY, m->ac & 0x80);
    m->ac = (m->ac << 1) & 0xFE;
    set_flags(m, m->ac);
    break;

case ASL_ZP:
    arg1 = NEXT_BYTE(m);
    set_flag(m, FLAG_CARRY, m->mem[arg1] & 0x80);
    m->mem[arg1] = (m->mem[arg1] << 1) & 0xFE;
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case ASL_ZPX:
    arg1 = ZP(NEXT_BYTE(m) + m->x);
    set_flag(m, FLAG_CARRY, m->mem[arg1] & 0x80);
    m->mem[arg1] = (m->mem[arg1] << 1) & 0xFE;
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case LSR_AB:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    set_flag(m, FLAG_CARRY, m->mem[r1] & 0x01);
    m->mem[r1] = (m->mem[r1] >> 1) & 0x7F;
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case LSR_ABX:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), m->x);
    set_flag(m, FLAG_CARRY, m->mem[r1] & 0x01);
    m->mem[r1] = (m->mem[r1] >> 1) & 0x7F;
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case LSR_ACC:
    set_flag(m, FLAG_CARRY, m->ac & 0x01);
    m->ac = (m->ac >> 1) & 0x7F;
    set_flags(m, m->ac);
    break;

case LSR_ZP:
    arg1 = NEXT_BYTE(m);
    set_flag(m, FLAG_CARRY, m->mem[arg1] & 0x01);
    m->mem[arg1] = (m->mem[arg1] >> 1) & 0x7F;
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case LSR_ZPX:
    arg1 = ZP(NEXT_BYTE(m) + m->x);
    set_flag(m, FLAG_CARRY, m->mem[arg1] & 0x01);
    m->mem[arg1] = (m->mem[arg1] >> 1) & 0x7F;
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case ROL_AB:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    t1 = m->mem[r1] & 0x80;
    m->mem[r1] = ((m->mem[r1] << 1) & 0xFE) | get_flag(m, FLAG_CARRY);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ROL_ABX:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), m->x);
    t1 = m->mem[r1] & 0x80;
    m->mem[r1] = ((m->mem[r1] << 1) & 0xFE) | get_flag(m, FLAG_CARRY);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ROL_ACC:
    t1 = m->ac & 0x80;
    m->ac = ((m->ac << 1) & 0xFE) | get_flag(m, FLAG_CARRY);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->ac);
    break;

case ROL_ZP:
    arg1 = NEXT_BYTE(m);
    t1 = m->mem[arg1] & 0x80;
    m->mem[arg1] = ((m->mem[arg1] << 1) & 0xFE) | get_flag(m, FLAG_CARRY);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case ROL_ZPX:
    arg1 = ZP(NEXT_BYTE(m) + m->x);
    t1 = m->mem[arg1] & 0x80;
    m->mem[arg1] = ((m->mem[arg1] << 1) & 0xFE) | get_flag(m, FLAG_CARRY);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case ROR_AB:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), 0);
    t1 = m->mem[r1] & 0x01;
    m->mem[r1] = ((m->mem[r1] >> 1) & 0x7F) | (get_flag(m, FLAG_CARRY) << 7);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ROR_ABX:
    arg1 = NEXT_BYTE(m);
    r1 = mem_abs(arg1, NEXT_BYTE(m), m->x);
    t1 = m->mem[r1] & 0x01;
    m->mem[r1] = ((m->mem[r1] >> 1) & 0x7F) | (get_flag(m, FLAG_CARRY) << 7);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[r1]);
    mark_dirty(m, r1);
    break;

case ROR_ACC:
    t1 = m->ac & 0x01;
    m->ac = ((m->ac >> 1) & 0x7F) | (get_flag(m, FLAG_CARRY) << 7);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->ac);
    break;

case ROR_ZP:
    arg1 = NEXT_BYTE(m);
    t1 = m->mem[arg1] & 0x01;
    m->mem[arg1] = ((m->mem[arg1] >> 1) & 0x7F) | (get_flag(m, FLAG_CARRY) << 7);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;

case ROR_ZPX:
    arg1 = ZP(NEXT_BYTE(m) + m->x);
    t1 = m->mem[arg1] & 0x01;
    m->mem[arg1] = ((m->mem[arg1] >> 1) & 0x7F) | (get_flag(m, FLAG_CARRY) << 7);
    set_flag(m, FLAG_CARRY, t1);
    set_flags(m, m->mem[arg1]);
    mark_dirty(m, arg1);
    break;
