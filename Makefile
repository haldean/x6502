CC=gcc
COPTS=-o x6502 -O3 -Wall
LIBS=-lncurses -lpthread
DEBUGOPTS=-DDEBUG -O0 -g
PYTHON=python

all: release

debug-names.h: generate_debug_names.py opcodes.h
	$(PYTHON) generate_debug_names.py > debug-names.h

release: debug-names.h *.c *.h
	$(CC) $(COPTS) *.c $(LIBS)

debug: debug-names.h *.c *.h
	$(CC) $(COPTS) $(DEBUGOPTS) *.c $(LIBS)

clean:
	rm -f debug-names.h x6502
