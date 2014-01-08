#include "io.h"

#include <ncurses.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

#include "functions.h"

#define VTERM_ROWS 40
#define VTERM_COLS 25

uint8_t io_modeflags = 0x00;

void init_vterm();
void update_vterm(cpu *, uint16_t);
void finish_vterm();

void init_io() {
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void finish_io() {
    if (io_modeflags & IO_MODEFLAG_VTERM) {
        finish_vterm();
    }
}

void init_vterm() {
    initscr();
    // reinit IO after initializing the ncurses window
    init_io();
}

void finish_vterm() {
    if (io_modeflags & IO_MODEFLAG_WAIT_TERMINATE) {
        // wait for user to hit enter to quit
        printw("\nterminated. hit any key to exit.");
        nodelay(stdscr, FALSE);
        getch();
    }
    endwin();
}

void update_modeflags(uint8_t old_flags, uint8_t new_flags) {
    io_modeflags = new_flags;

    if ((new_flags ^ old_flags) & IO_MODEFLAG_VTERM) {
        if (new_flags & IO_MODEFLAG_VTERM) {
            init_vterm();
        } else {
            finish_vterm();
        }
    }
}

void update_vterm(cpu *m, uint16_t dirty) {
    uint16_t offset = dirty - IO_VTERM_START;
    if (offset >= 1000) {
        // this is in the unused 24 bytes at the end of the page, ignore it
        return;
    }
    uint8_t r = offset / VTERM_COLS;
    uint8_t c = offset % VTERM_COLS;
    mvprintw(r, c, "%c", m->mem[dirty]);
}

void handle_io(cpu *m) {
    int read;
    if ((read = getch()) != ERR) {
        m->interrupt_waiting = 0x01;
        m->mem[IO_GETCHAR] = read;
    }

    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        uint16_t addr = m->dirty_mem_addr;
        if (addr == IO_PUTCHAR) {
            if (io_modeflags & IO_MODEFLAG_VTERM) {
                addch(m->mem[addr]);
                refresh();
            } else {
                printf("%c", m->mem[addr]);
            }
        } else if (addr == IO_MODEFLAGS) {
            update_modeflags(io_modeflags, m->mem[IO_MODEFLAGS]);
        } else if (IO_VTERM_START <= addr && addr < IO_VTERM_END) {
            update_vterm(m, addr);
        }
    }
}
