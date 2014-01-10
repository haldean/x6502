        lda     #$01
        sta     $FF02

        lda     #$00
        sta     $FEE8

        lda     #$41
        ldx     #$00
        ldy     #$08

loop
        sta     $FB00,X
        inx
        sta     $FB00,X
        inx
        sta     $FB00,X
        inx

        inc     $FEE8
        cpy     $FEE8
        bne     loop

        wai
