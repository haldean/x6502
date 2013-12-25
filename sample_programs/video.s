#include <stdio.s>

 ; enable video
        lda     vflag
        ora     vflag_enable
        sta     vflag

 ; load color table (all red)
        lda     #%00000001
        ldx     #$00
ctab:   sta     $EF40,X
        debug
        inx
        ina
        cpx     #$10
        bne     ctab

        ldx     #$00
        lda     #$00
ld:     sta     $D000,X
        inx
        jsr     next
        cpx     #$FF
        bne     ld

 ; flip display
        lda     vflag
        ora     #$02
        sta     vflag

loop:   nop
        jmp loop

next:   and     #$0F
        adc     #$01
        sta     $0200
        asl
        asl
        asl
        asl
        ora     $0200
        rts
