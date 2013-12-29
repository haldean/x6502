            ldx     #$80        ; Load value #80 into X register
decrement:  dex                 ; Decrement value in X register
            cpx     #$31        ; Compare the value in X register with '1'
            bne     decrement   ; In not equal go to decrement
            stx     $FF00       ; Outpot value in X
            
            lda     #$0A        ; load '\n'
            sta     $FF00       ; output new line