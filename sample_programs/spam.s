counter = $0100

        lda     #$03    ; set WAIT_TERMINATE flag
        sta     $FF02

        lda     #$FF
        sta     counter ; init counter

        ldx     #$0

loop    lda     #$41    ; 41 == 'A'
        sta     $FF00,X
        inx
        cpx     counter
        bne     loop
