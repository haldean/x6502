temp:
       .byte    0
       
; calculate the sum of numbers from 0 to 10

        ldx     #$00    ; counter
        lda     #$00    ; the sum
loop:
        stx     temp    ; store the value
        adc     temp    ; add the value to accumulator
        inx             ; increment x
        cpx     #$0A    ; compare x with A
        bne     loop    ; repeat if not equal
        
; display the value as char
        
        sta     $FF00   ; display 45 as '-'

        lda     #$0A    ; break the line
        sta     $FF00