CC=clang
PYTHON=python
COPTS=-o x6502 -O3 -lpthread -pthread -Wall
DEBUGOPTS=-DDEBUG -O0 -g

XA=xa
XAOPTS=-bt0 -Istdlib/
XASRC=$(wildcard sample_programs/*.s)
XAOBJ=$(XASRC:.s=.o)

all: release $(XAOBJ)

sample_programs/%.o: sample_programs/%.s
	$(XA) $(XAOPTS) -o $@ $<

debug-names.h: generate_debug_names.py opcodes.h
	$(PYTHON) generate_debug_names.py > debug-names.h

release: debug-names.h *.c *.h
	$(CC) $(COPTS) *.c

debug: debug-names.h *.c *.h
	$(CC) $(COPTS) $(DEBUGOPTS) *.c