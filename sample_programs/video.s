#include <stdio.s>

 ; enable video
        lda     vflag
        ora     vflag_enable
        sta     vflag

 ; load color table
 ; 00: red
 ; 01: green
 ; 02: blue
        lda     #%11100000
        sta     $EF40
        lda     #%00011100
        sta     $EF41
        lda     #%00000011
        sta     $EF42

loop:
        ldx     #$00
        lda     #$00

ld1:    sta     $D000,X
        inx
        cpx     #$FF
        bne     ld1

        lda     vflag
        ora     vflag_flip
        sta     vflag

jnop:   nop
        jmp jnop
