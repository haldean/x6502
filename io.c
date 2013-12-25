#include "io.h"

#include <pthread.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>

#include "functions.h"
#include "video.h"

#define INPUT_BUFFER_SIZE 1024

pthread_t read_thread;
struct termios tty_restore;

char input_buffer[1024];
int16_t next_read = 0;
int16_t next_write = 0;

void * read_thread_func(void *unused) {
    int read;
    for (;;) {
        if ((read = fgetc(stdin)) != EOF) {
            input_buffer[next_write++] = read;
            if (next_write >= INPUT_BUFFER_SIZE) {
                next_write = 0;
            }
            if (next_write == next_read) {
                printf("WARNING: input coming in too fast, "
                        "input buffer is about to be overwritten.\n");
            }
        } else {
            break;
        }
    }
    return NULL;
}

void init_io() {
    struct termios tty_state;
    tcgetattr(fileno(stdin), &tty_restore);
    tcgetattr(fileno(stdin), &tty_state);

    tty_state.c_lflag &= ~(ICANON | ECHO);
    tty_state.c_cc[VMIN] = 1;

    tcsetattr(fileno(stdin), TCSANOW, &tty_state);

    pthread_create(&read_thread, NULL, read_thread_func, NULL);
}

void finish_io() {
    tcsetattr(fileno(stdin), TCSANOW, &tty_restore);
}

int handle_io(cpu *m) {
    if (next_read != next_write) {
        m->interrupt_waiting = 0x01;
        m->mem[IO_GETCHAR] = input_buffer[next_read++];
        if (next_read >= INPUT_BUFFER_SIZE) {
            next_read = 0;
        }
    }

    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        if (m->dirty_mem_addr == IO_PUTCHAR) {
            putchar(m->mem[m->dirty_mem_addr]);
            fflush(stdout);
        }
    }

    return handle_video(m);
}
