case BCC_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_CARRY)) {
        branch_offset = s1;
    }
    break;

case BCS_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_CARRY)) {
        branch_offset = s1;
    }
    break;

case BEQ_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_ZERO)) {
        branch_offset = s1;
    }
    break;

case BMI_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_NEGATIVE)) {
        branch_offset = s1;
    }
    break;

case BNE_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_ZERO)) {
        branch_offset = s1;
    }
    break;

case BPL_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_NEGATIVE)) {
        branch_offset = s1;
    }
    break;

case BVC_REL:
    s1 = NEXT_BYTE(m);
    if (!get_flag(m, FLAG_OVERFLOW)) {
        branch_offset = s1;
    }
    break;

case BVS_REL:
    s1 = NEXT_BYTE(m);
    if (get_flag(m, FLAG_OVERFLOW)) {
        branch_offset = s1;
    }
    break;
