# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall

snip: src/main.c
	$(CC) $(CFLAGS) src/main.c -o snip
