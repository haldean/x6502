#include <stdio.s>

; $00   low byte of character address
; $01   high byte of character address

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
        clc

        lda     $00
        adc     #cols
        sta     $00

        lda     $01
        adc     #$00
        sta     $01

        jmp     checkbounds

checkk:
        cmp     #$6B    ; 6B == 'k'
        bne     checkh
        ; it's a k. move up.
        sec

        lda     $00
        sbc     #cols
        sta     $00

        lda     $01
        sbc     #$00
        sta     $01

        jmp     checkbounds

checkh:
        cmp     #$68    ; 68 == 'h'
        bne     checkl
        ; it's an h. move left.
        sec

        lda     $00
        sbc     #$02
        sta     $00

        lda     $01
        sbc     #$00
        sta     $01

        jmp     checkbounds

checkl:
        cmp     #$6C    ; 6C == 'l'
        bne     done
        ; it's an l. move right.
        clc

        lda     $00
        adc     #$02
        sta     $00

        lda     $01
        adc     #$00
        sta     $01

        jmp     checkbounds

checkbounds:
checked:
done:
        pla
        rti
