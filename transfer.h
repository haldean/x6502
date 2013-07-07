case TAX:
    m->x = m->ac;
    set_flags(m, m->x);
    break;

case TAY:
    m->y = m->ac;
    set_flags(m, m->y);
    break;

case TSX:
    m->x = m->sp;
    set_flags(m, m->x);
    break;

case TXA:
    m->ac = m->x;
    set_flags(m, m->ac);
    break;

case TXS:
    m->sp = m->x;
    break;

case TYA:
    m->ac = m->y;
    set_flags(m, m->ac);
    break;
