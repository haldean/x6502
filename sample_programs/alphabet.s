        lda     #$02    ; set WAIT_TERMINATE flag
        sta     $FF02
        lda     #$41    ; 41 == 'A'
        sta     $FF00
        lda     #$5A    ; 5A == 'Z'
loop    inc     $FF00
        cmp     $FF00
        bne     loop
        lda     #$0A    ; 0A == '\n'
        sta     $FF00
