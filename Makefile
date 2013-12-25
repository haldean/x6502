CC=clang
PYTHON=python
COPTS=-o x6502 -O3 -lpthread -lSDL -Wall
DEBUGOPTS=-DDEBUG -O0 -g

all: release

debug-names.h: generate_debug_names.py opcodes.h
	$(PYTHON) generate_debug_names.py > debug-names.h

release: debug-names.h *.c *.h
	$(CC) $(COPTS) *.c

debug: debug-names.h *.c *.h
	$(CC) $(COPTS) $(DEBUGOPTS) *.c
