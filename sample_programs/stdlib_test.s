#include <stdio.s>

    lda     #$02    ; set WAIT_TERMINATE flag
    sta     iomode
    lda     #<str
    sta     $F0
    lda     #>str
    sta     $F1
    jsr     print

    lda     #$00
    sta     blck0_addrl
    sta     blck0_addrh
    jsr     fread
    jsr     print

    lda     #$00
    sta     blck0_addrl
    lda     #$FF
    sta     blck0_addrh
    jsr     fread
    jsr     print

    ext

str: .asc "hello, world, from .data!", $0A, $00
