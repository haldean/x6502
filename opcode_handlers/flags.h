case CLC:
    set_flag(m, FLAG_CARRY, 0);
    break;

case CLD:
    set_flag(m, FLAG_DECIMAL, 0);
    break;

case CLI:
    set_flag(m, FLAG_INTERRUPT, 0);
    break;

case CLV:
    set_flag(m, FLAG_OVERFLOW, 0);
    break;

case SEC:
    set_flag(m, FLAG_CARRY, 1);
    break;

case SED:
    set_flag(m, FLAG_DECIMAL, 1);
    break;

case SEI:
    set_flag(m, FLAG_INTERRUPT, 1);
    break;
