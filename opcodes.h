#ifndef __6502_OPCODES__
#define __6502_OPCODES__

#define OPCODE_CYCLES(opcode) 1

#define BRK     0x00

#define LDA_AB  0xAD
#define LDA_ABX 0xBD
#define LDA_ABY 0xB9
#define LDA_IMM 0xA9
#define LDA_INX 0xA1
#define LDA_INY 0xB1
#define LDA_ZP  0xA5
#define LDA_ZPX 0xB5

#define LDX_AB  0xAE
#define LDX_ABY 0xBE
#define LDX_IMM 0xA2
#define LDX_ZP  0xA6
#define LDX_ZPY 0xB6

#define LDY_AB  0xAC
#define LDY_ABX 0xBC
#define LDY_IMM 0xA0
#define LDY_ZP  0xA4
#define LDY_ZPX 0xB4

#endif
