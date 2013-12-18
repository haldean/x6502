#!/bin/bash

python generate_debug_names.py > debug-names.h
clang *.c -o x6502 -O3
