; Push the values from '0' to '9' into stack, and pull them back with output

        ldx     #$30        ; load #30 into X - current character
        ldy     #$00        ; load #30 into Y - the loop counter
        
                            ; Push the values into stack
loop1   txa                 ; Transfer X to accumulator
        pha                 ; Push the value from accumulator into stack
        inx                 ; Increase X
        iny                 ; Increase Y
        cpy     #$0A        ; Compare Y with #a
        bne     loop1       ; If not equal #a go to loop1
        
                            ; Fetch the values back from the stack
loop2   pla                 ; Pull value from stack into accumulator
        sta     $FF00       ; Display the value from accumulator
        dey                 ; Decrease the value in Y
        cpy     #$00        ; Compare Y with #0
        bne     loop2       ; If not equal #0 go to loop2
        
        lda     #$0A        ; Load '\n'
        sta     $FF00       ; Output new line