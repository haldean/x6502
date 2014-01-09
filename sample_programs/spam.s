counter = $0100
supercounter = $0101
page = $FF
char = $FD

        lda     #$01    ; go into vterm mode
        sta     $FF02

        lda     #$FF
        sta     counter ; init counter

        lda     #$FB
        sta     page
        lda     #$00
        sta     page-1

        lda     #$41    ; 41 == 'A'
        sta     char

        ldy     #$00

loop:
        lda     char
        sta     (page-1),Y
        jsr     incchar

        iny
        cpy     #$00
        bne     loop

        inc     page
        lda     page
        cmp     #$FF
        bne     loop

        wai
        .byt    $FF

incchar:
        inc     char
        lda     char
        cmp     #$5B
        bne     chardone
        lda     #$41
chardone:
        sta     char
        rts
