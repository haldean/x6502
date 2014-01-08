CC=clang
COPTS=-o x6502 -O3 -lpthread -Wall
DEBUGOPTS=-DDEBUG -O0 -g

all: release

debug-names.h: generate_debug_names opcodes.h
	./generate_debug_names < opcodes.h > debug-names.h

release: debug-names.h *.c *.h
	$(CC) $(COPTS) *.c

debug: debug-names.h *.c *.h
	$(CC) $(COPTS) $(DEBUGOPTS) *.c
