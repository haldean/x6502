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

#define NOP     0xEA

#define STA_AB  0x8D
#define STA_ABX 0x9D
#define STA_ABY 0x99
#define STA_INX 0x81
#define STA_INY 0x91
#define STA_ZP  0x85
#define STA_ZPX 0x95

#define STX_ZP  0x86
#define STX_ZPY 0x96
#define STX_AB  0x8E

#define STY_ZP  0x84
#define STY_ZPX 0x94
#define STY_AB  0x8C

#define TAX     0xAA
#define TAY     0xA8
#define TSX     0xBA
#define TXA     0x8A
#define TXS     0x9A
#define TYA     0x98

#endif
