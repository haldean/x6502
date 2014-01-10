#include <stdio.s>

rows = 25
cols = 40

; load location of ISR
        lda     #<isr
        sta     $FFFE
        lda     #>isr
        sta     $FFFF

; activate vterm mode
        lda     #$01
        sta     $FF02

; shiny pretty colors
        lda     #$04
        sta     paint

; register and addressing init
        lda     #$00
        sta     $00
        lda     #$FB
        sta     $01

        lda     #$A4
        ldy     #$00

        cli

loop
        sta     ($00),Y
        wai
        jmp     loop

isr:
        pha

        ; clear existing character
        lda     #$20
        sta     ($00),Y

        lda     getc

        cmp     #$71    ; 71 == 'q'
        bne     checkj
        ext

checkj:
        cmp     #$6A    ; 6A == 'j'
        bne     checkk
        ; it's a j. move down.
        tya
        clc
        adc     #cols
        jmp     checkbounds

checkk:
        cmp     #$6B    ; 6B == 'k'
        bne     checkh
        ; it's a k. move up.
        tya
        sec
        sbc     #cols
        jmp     checkbounds

checkh:
        cmp     #$68    ; 68 == 'h'
        bne     checkl
        ; it's an h. move left.
        tya
        sec
        sbc     #$02
        jmp     checkbounds

checkl:
        cmp     #$6C    ; 6C == 'l'
        bne     done
        ; it's an h. move left.
        tya
        clc
        adc     #$02
        jmp     checkbounds

checkbounds:
        ; TODO
        tay

done:
        pla
        rti
