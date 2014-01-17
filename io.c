#include "io.h"

#include <ncurses.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

#include "functions.h"

#define VTERM_ROWS 25
#define VTERM_COLS 40

uint8_t io_modeflags = 0x00;
uint8_t io_supports_paint;

WINDOW *window = NULL;

void init_vterm();
void update_vterm(cpu *, uint16_t);
void finish_vterm();

void init_io() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    io_supports_paint = (has_colors() != FALSE);
    if (io_supports_paint) {
        start_color();
        for (int i = 0; i < 8; i++) {
            init_pair(i, i, COLOR_BLACK);
        }
    }
}

void finish_io() {
    if (io_modeflags & IO_MODEFLAG_WAIT_HALT) {
        nodelay(stdscr, FALSE);
        printw("\nterminated, press any key to exit.\n");
        getch();
    }

    if (io_modeflags & IO_MODEFLAG_VTERM) {
        finish_vterm();
    }
}

void init_vterm() {
    window = newwin(VTERM_ROWS + 2, VTERM_COLS + 2, 0, 0);
    box(window, 0, 0);
    wrefresh(window);
}

void finish_vterm() {
    endwin();
}

void update_modeflags(uint8_t old_flags, uint8_t new_flags) {
    io_modeflags = new_flags;

    // if the vterm flag changed (avoids reinit every time flags change)
    if ((new_flags ^ old_flags) & IO_MODEFLAG_VTERM) {
        if (new_flags & IO_MODEFLAG_VTERM) {
            init_vterm();
        } else {
            finish_vterm();
        }
    }
}

void update_paint(uint8_t paint) {
    wattrset(window,
            COLOR_PAIR(paint & 0x0F) |
            (paint & IO_PAINT_DIM ? A_DIM : 0) |
            (paint & IO_PAINT_UNDERLINE ? A_UNDERLINE : 0) |
            (paint & IO_PAINT_BOLD ? A_BOLD : 0));
}

void update_vterm(cpu *m, uint16_t dirty) {
    uint16_t offset = dirty - IO_VTERM_START;
    if (offset >= 1000) {
        // this is in the unused 24 bytes at the end of the page, ignore it
        return;
    }
    // 1 offsets to avoid overwriting the border
    uint8_t r = offset / VTERM_COLS + 1;
    uint8_t c = offset % VTERM_COLS + 1;
    mvwprintw(window, r, c, "%c", m->mem[dirty]);
    wrefresh(window);
}

void handle_io(cpu *m) {
    int read;
    if ((read = getch()) != ERR) {
        m->interrupt_waiting = 0x01;
        m->mem[IO_GETCHAR] = read;
    }

    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        uint16_t addr = m->dirty_mem_addr;

#ifdef DEBUG
        fprintf(stderr, "dirty address %04X has value %02x\n",
                addr, m->mem[addr]);
#endif

        if (addr == IO_PUTCHAR) {
            if (io_modeflags & IO_MODEFLAG_VTERM) {
                wprintw(window, "%c", m->mem[addr]);
                wrefresh(window);
            } else {
                addch(m->mem[addr]);
            }
        } else if (addr == IO_MODEFLAGS) {
            update_modeflags(io_modeflags, m->mem[IO_MODEFLAGS]);
        } else if (addr == IO_PAINT) {
            update_paint(m->mem[addr]);
        } else if (IO_VTERM_START <= addr && addr < IO_VTERM_END) {
            update_vterm(m, addr);
        }
    }
}
