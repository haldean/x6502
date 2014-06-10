; defines useful constants for writing 6502 assembler that targets x6502

putc            = $FF00
getc            = $FF01

vflag           = $FF02
vflag_enable    = $01
vflag_flip      = $02

#define debug .byt $FC
#define ext .byt $FF
#define DEBUG debug
#define EXT ext
