#ifndef __6502_OPCODES__
#define __6502_OPCODES__

#define OPCODE_CYCLES(opcode) 1

// Opcode constants that have multiple addressing modes are named in the form
// X_Y, where X is the instruction and Y is the addressing mode. The possible
// addressing modes are:
//      AB:  absolute mode, next two bytes are the low/high byte of an absolute
//           memory address
//      ABX: absolute,X, next two bytes are added to the value in register X to
//           get the memory address
//      ABY: same as ABX, except the value of register Y is used instead of X
//      IMM: next byte is a constant to be used instead of a lookup
//      INX: (indirect,X) mode, add X to the following byte, modulo 0xFF, and
//           lookup two bytes starting at that location. Those two bytes form
//           the memory address that will be used
//      INY: (indirect),Y mode, look up two bytes starting at address in the
//           following byte, add Y modulo 0xFFFF, and use the result as an
//           address
//      ZP:  zero-page, next byte is the low bits of the memory address (can
//           only address first 256 bytes of memory using ZP)
//      ZPX: zero-page,X, add next byte to X modulo 0xFF and use that as a
//           memory address

#define ADC_AB  0x6D
#define ADC_ABX 0x7D
#define ADC_ABY 0x79
#define ADC_IMM 0x69
#define ADC_INX 0x61
#define ADC_INY 0x71
#define ADC_ZP  0x65
#define ADC_ZPX 0x75

#define AND_AB  0x2D
#define AND_ABX 0x3D
#define AND_ABY 0x39
#define AND_IMM 0x29
#define AND_INX 0x21
#define AND_INY 0x31
#define AND_ZP  0x25
#define AND_ZPX 0x35

#define BIT_AB  0x2C
#define BIT_ZP  0x24

#define BRK     0x00

#define EOR_AB  0x4D
#define EOR_ABX 0x5D
#define EOR_ABY 0x59
#define EOR_IMM 0x49
#define EOR_INX 0x41
#define EOR_INY 0x51
#define EOR_ZP  0x45
#define EOR_ZPX 0x55

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

#define ORA_IMM 0x09
#define ORA_ZP  0x05
#define ORA_ZPX 0x15
#define ORA_AB  0x0D
#define ORA_ABX 0x1D
#define ORA_ABY 0x19
#define ORA_INX 0x01
#define ORA_INY 0x11

#define NOP     0xEA

#define PHA     0x48
#define PHP     0x08
#define PLA     0x68
#define PLP     0x28

#define SBC_IMM 0xE9
#define SBC_ZP  0xE5
#define SBC_ZPX 0xF5
#define SBC_AB  0xED
#define SBC_ABX 0xFD
#define SBC_ABY 0xF9
#define SBC_INX 0xE1
#define SBC_INY 0xF1

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
