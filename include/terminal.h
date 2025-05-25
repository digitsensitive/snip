#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> //  ioctl(), TIOCGWINSZ, struct winsize
#include <termios.h> // struct termios, tcgetattr(), tcsetattr(), all flags, TCSAFLUSH
#include <unistd.h> // STDIN_FILENO

#include "types.h"

typedef struct {
  struct winsize ws; // https://man.archlinux.org/man/TIOCGWINSZ.2const
  struct termios orig_termios;
  struct termios raw_termios;
} Terminal;

void init_terminal();
void print_termios_flags(struct termios *term);
void enable_raw_mode();
void disable_raw_mode();
int get_window_size(uint *rows, uint *cols);
void die(const char *s);
