; defines useful constants and methods for writing 6502 assembler that targets x6502

#define debug .byt $FC
#define ext .byt $FF
#define DEBUG debug
#define EXT ext

.(
jmp prog

+putc = $FF00
+getc = $FF01
+iomode = $FF02
+paint = $FEE8

+blck0_addrl = $FF03
+blck0_addrh = $FF04
+blck0_read = $FF05
+blck0_write = $FF06
+blck0_err = $FF07

; print reads two bytes from $00F0, treats them as a memory address, then
; reads from that memory address and prints those characters to the character
; device until a NUL character is found. the printed string must be less than
; 256 characters long.
+print:
.(
    pha
    ldy     #$00
loop:
    lda     ($F0),Y
    cmp     #$00
    beq     done
    sta     putc
    iny
    ; check that y hasn't overflowed
    cpy     #$00
    beq     done
    jmp     loop
done:
    pla
    rts
.)

; fread reads up to 255 bytes into a memory region that starts at the address in
; $00F0 from the current position of the block device until a null character is
; encountered.
+fread:
.(
    pha
    ldy     #$00

loop:
    lda     blck0_read
    ; TODO check read status

    sta     ($F0),Y

    iny
    ; check that y hasn't overflowed
    cpy     #$00
    beq     done

    ; increment disk address, using carry addition
    clc
    lda     #$01
    adc     blck0_addrl
    sta     blck0_addrl
    lda     #$00
    adc     blck0_addrh
    sta     blck0_addrh

    jmp     loop

done:
    pla
    rts
.)

prog:
.)
