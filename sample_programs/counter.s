; Instructions set http://www.obelisk.demon.co.uk/6502/reference.html
;
        lda     #$30    ; Loads a byte of memory into the accumulator.
                        ; '0' is loaded into the accumulator
        sta     $FF00   ; Stores the contents of the accumulator
                        ; into memory. Storing to $FF00 outputs the character
        lda     #$39    ; Load '9' into the accumulator for later comparison
loop    inc     $FF00   ; Adds one to the value held at a specified
                        ; memory location. This also outputs the stored value
                        ; to the terminal 
        cmp     $FF00   ; Comparee the contents of the accumulator
                        ; with another memory held value. This operation sets zero flag
                        ; if both values are equal
        bne     loop    ; If the zero flag is clear then add the relative
                        ; displacement to the program counter to cause
                        ; a branch to a new location.
        lda     #$0A    ; Load '\n' into the accumulator 
        sta     $FF00   ; Push the newline character to output
