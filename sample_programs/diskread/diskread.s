        cli
        lda     #$02    ; set WAIT_TERMINATE flag
        sta     $FF02
        lda     #$03
        sta     $FF03
        lda     #$00
        sta     $FF04
        lda     #$00
        cmp     $FF07
        beq     printchar
        lda     #'e'
        sta     $FF00
        lda     #'r'
        sta     $FF00
        sta     $FF00
        jmp     done
printchar:
        lda     $FF05
        sta     $FF00
done:
