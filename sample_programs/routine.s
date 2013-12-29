temp:
       .byte    0
       
; multiply 9 by 10

        lda     #$09    ; store 9 in the accumulator
        jsr     mult10  ; call the routine
        sta     $FF00   ; display the value 'Z' (char 90)
        jmp     done    ; end the execution

; By Leo Nechaev (leo@ogpi.orsk.ru)
mult10:
        asl             ; multiply by 2
        sta     temp    ; store the double at the temp location
        asl             ; again multiply by 2 (*4)
        asl             ; again multiply by 2 (*8)
        clc             ; clear carry flags
        adc     temp    ; add the double value to accumulator
                        ; as result, A = x * 8 + x * 2
        rts             ; return from subroutine

done:
        lda     #$0A    ; break the line
        sta     $FF00