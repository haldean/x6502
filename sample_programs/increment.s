lda     #$40    ; store '@' in the accumulator
tax             ; transfer value from accumulator to X register
inx             ; increment value in the X register
stx     $FF00   ; output the value 'A'

lda     #$0A    ; load '\n'
sta     $FF00   ; output new line