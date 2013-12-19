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
        cpx     $FF01
        .byt    $FC     ; dump command
        bcs     chekz   ; if val is >= a, all good so far, skip to z check
        jmp     noup    ; if val is < a, don't transform it

; check if char is greater than 'z'
chekz   ldx     #$7B    ; == 'z' + 1
        cpx     $FF01
        .byt    $FC     ; dump command
        bcs     noup    ; if val is >= z + 1, don't transform it

        lda     #$E0    ; 'A' - 'a'
        adc     $FF01
        jmp     done

noup    lda     $FF01
done    sta     $FF00
        pla
        rti
        .word $0000, loop
