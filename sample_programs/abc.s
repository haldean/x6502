; This program outputs ABC on the terminal

lda     #$41    ; load 'A' into accumulator
sta     $FF00   ; transfer into stdout
lda     #$42    ; load 'B'
sta     $FF00
lda     #$43    ; load 'B'
sta     $FF00

lda     #$0A    ; load '\n'
sta     $FF00