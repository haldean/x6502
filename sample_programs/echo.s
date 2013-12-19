; echos everything to the terminal, transforming lowercase into uppercase

#include <stdio.s>

; load location of ISR and enable interrupts
        lda     #<isr
        sta     $FFFE
        lda     #>isr
        sta     $FFFF
        cli

; wait for input
loop    nop
        jmp     loop

; start ISR
isr     pha

; check if char is less than 'a'
cheka   ldx     #$60    ; == 'a' - 1
        cpx     getc
        bcs     noup    ; if val is < a, don't transform it

; check if char is greater than 'z'
chekz   ldx     #$7B    ; == 'z' + 1
        cpx     getc
        bcc     noup    ; if val is >= z + 1, don't transform it

; lower -> upper
        lda     #$DF    ; 'A' - 'a'
        adc     getc
        jmp     done

; print and return
noup    lda     getc
done    sta     putc
        pla
        rti
