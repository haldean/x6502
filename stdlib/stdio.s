; defines useful constants for writing 6502 assembler that targets x6502

putc = $FF00
getc = $FF01
iomode = $FF02
paint = $FEE8

#define debug .byt $FC
#define ext .byt $FF
#define DEBUG debug
#define EXT ext
