        ldx     #$00            ; Start with 0 offset
loop:   lda     message, x      ; Load data from string to a
        beq     done            ; If 0 is read we're done
        sta     $FF00           ; Output the character
        inx                     ; Increment X
        bne     loop            ; In index doesn't overflow to 0 repeat
        
done:        

message:
        .byte   "Hello World!", $0A, $00