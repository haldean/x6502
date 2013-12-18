#ifndef __6502_CPU__
#define __6502_CPU__

#include <stdint.h>

#define MEMORY_SIZE 65536
#define INTERRUPT_PERIOD 100
#define STACK_START 0x0100

#define FLAG_NEGATIVE 0x80
#define FLAG_OVERFLOW 0x40
#define FLAG_BREAK 0x10
#define FLAG_DECIMAL 0x08
#define FLAG_INTERRUPT 0x04
#define FLAG_ZERO 0x02
#define FLAG_CARRY 0x01

#define EMU_FLAG_DIRTY 0x01

typedef struct {
    // program counter
    uint16_t pc;
    // index registers
    uint8_t x, y;
    // stack pointer
    uint8_t sp;
    // accumulator
    uint8_t ac;
    // status register
    uint8_t sr;
    // emulator flag register (not in 6502 spec, not accessible from assembler)
    uint8_t emu_flags;

    uint8_t interrupt_waiting;

#ifdef DEBUG
    uint8_t last_opcode;
#endif

    // RAM
    uint8_t mem[MEMORY_SIZE];

    // stores the address of memory modified by the last instruction
    uint16_t dirty_mem_addr;
} cpu;

cpu * new_cpu();

#endif
