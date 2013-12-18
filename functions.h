#ifndef __6502_FUNCTIONS__
#define __6502_FUNCTIONS__

#include "cpu.h"

#define ZP(x) ((uint8_t) (x))
#define STACK_PUSH(m) (m)->mem[(m)->sp-- + STACK_START]
#define STACK_POP(m) (m)->mem[++(m)->sp + STACK_START]

static inline size_t mem_abs(uint8_t low, uint8_t high, uint8_t off) {
    return (uint16_t) off + (uint16_t) low + ((uint16_t) high << 8);
}

static inline size_t mem_indirect_index(cpu *m, uint8_t addr, uint8_t off) {
    return mem_abs(m->mem[addr], m->mem[addr+1], off);
}

static inline size_t mem_indexed_indirect(cpu *m, uint8_t addr, uint8_t off) {
    return mem_abs(m->mem[addr+off], m->mem[addr+off+1], 0);
}

// set arg MUST be 16 bits, not 8, so that add results can fit into set.
static inline void set_flag(cpu *m, uint8_t flag, uint16_t set) {
    if (set) {
        m->sr |= flag;
    } else {
        m->sr &= ~flag;
    }
}

static inline uint8_t get_flag(cpu *m, uint8_t flag) {
    return (m->sr & flag) > 0;
}

static inline uint8_t get_emu_flag(cpu *m, uint8_t flag) {
    return (m->emu_flags & flag) > 0;
}

// set flags for the result of a computation. set_flags should be called on the
// result of any arithmetic operation.
static inline void set_flags(cpu *m, uint8_t val) {
    set_flag(m, FLAG_ZERO, !val);
    set_flag(m, FLAG_NEGATIVE, val & 0x80);
}

static inline uint8_t bcd(uint8_t val) {
    // bcd is "binary coded decimal"; it treats the upper nibble and lower
    // nibble of a byte each as a decimal digit, so 01011000 -> 0101 1000 -> 58.
    // in other words, treat hex output as decimal output, so 0x58 is treated as
    // 58. this is dumb and adds a bunch of branching to opcode interpretation
    // that I Do Not Like.
    return 10 * (val >> 4) + (0x0F & val);
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

static inline void cmp(cpu *m, uint8_t mem, uint8_t reg) {
    set_flag(m, FLAG_CARRY, reg >= mem);
    set_flag(m, FLAG_ZERO, reg == mem);
    set_flag(m, FLAG_NEGATIVE, 0x80 & (reg - mem));
}

// called at the start of processing an instruction to reset instruction-local
// emulator state
static inline void reset_emu_flags(cpu *m) {
    m->emu_flags = 0x00;
}

// mark a memory address as dirty
static inline void mark_dirty(cpu *m, uint16_t addr) {
    m->emu_flags |= EMU_FLAG_DIRTY;
    m->dirty_mem_addr = addr;
}

#endif
