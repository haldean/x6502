#include "video.h"

#include <SDL/SDL.h>

#include "functions.h"
#include "io.h"

#define PIXEL_SCALE 1

uint8_t video_enabled = 0x00;
SDL_Surface *output;
SDL_Event last_event;

uint32_t color_table[IO_VCOLORS];

void flip_video(cpu *m) {
    uint16_t i;
    uint16_t mem_addr;
    uint8_t color;

    SDL_LockSurface(output);
    for (i = 0; i < IO_VPIXELS; i++) {
        mem_addr = i / 2 + IO_VSTART;
        color = 0x0F & (m->mem[mem_addr] >> (i % 2 ? 4 : 0));
        ((uint32_t *) output->pixels)[i] = color_table[color];
    }
    SDL_UnlockSurface(output);
    SDL_Flip(output);
}

void update_pixel(cpu *m, uint8_t changed_addr) {

}

void update_ctable(cpu *m) {
    uint16_t i;
    uint16_t mem_addr;

    printf("ctab: ");
    for (i = 0; i < IO_VCOLORS; i++) {
        mem_addr = i + IO_VCTABS;
        color_table[i] = (IO_VRBITS & m->mem[mem_addr]) << 16;
        color_table[i] |= (IO_VGBITS & m->mem[mem_addr]) << 11;
        color_table[i] |= (IO_VBBITS & m->mem[mem_addr]) << 6;
        printf("%08X  ", color_table[i]);
    }
    printf("\n");
    flip_video(m);
}

void init_video(cpu *m) {
    SDL_Init(SDL_INIT_VIDEO);
    output = SDL_SetVideoMode(
            PIXEL_SCALE * IO_VWIDTH, PIXEL_SCALE * IO_VHEIGHT,
            32, SDL_SWSURFACE);
    video_enabled = 0x01;
    update_ctable(m);
}

void finish_video() {
    SDL_Quit();
    video_enabled = 0x00;
}

int handle_video(cpu *m) {
    if (get_emu_flag(m, EMU_FLAG_DIRTY)) {
        uint16_t addr = m->dirty_mem_addr;
        uint8_t val = m->mem[m->dirty_mem_addr];

        if (!video_enabled && addr != IO_VMODE) {
            return IO_OK;
        }

        if (addr == IO_VMODE) {
            if ((val & IO_VFLAG_ENABLE) && !video_enabled) {
                init_video(m);
            } else if (!video_enabled) {
                // bail early, everything else requires video to be enabled
                return IO_OK;
            }

            if ((val & IO_VFLAG_ENABLE) == 0) {
                finish_video();
            }

            if (val & IO_VFLAG_FLIP) {
                flip_video(m);
                m->mem[addr] ^= IO_VFLAG_FLIP;
            }
        } else if (IO_VSTART <= addr && addr < IO_VEND) {
            update_pixel(m, addr);
        } else if (IO_VCTABS <= addr && addr < IO_VCTABE) {
            update_ctable(m);
        }
    }

    if (video_enabled) {
        while (SDL_PollEvent(&last_event)) {
            switch (last_event.type) {
                case SDL_KEYDOWN:
                    if (last_event.key.keysym.sym == SDLK_ESCAPE) {
                        return IO_HALT;
                    }
                    break;

                case SDL_QUIT:
                    return IO_HALT;
            }
        }
    }

    return IO_OK;
}
