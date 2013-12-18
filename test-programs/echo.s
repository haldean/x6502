        lda     #<isr
        sta     $FFFE
        lda     #>isr
        sta     $FFFF   ; set the location of the isr
loop    nop
        jmp     loop
isr     pha
        lda     $FF01
        sta     $FF00
        pla
        rti
        .word $0000, loop
