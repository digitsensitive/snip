#pragma once

#include <termios.h> // struct termios
#include <time.h>    // time_t

#include "types.h"

typedef struct {
  uint size;
  uint rsize;
  char *chars;
  char *render;
} erow;

typedef struct {
  uint cx;
  uint cy;
  uint rx;
  uint rowoff;
  uint coloff;
  uint screenrows;
  uint screencols;
  uint numrows;
  erow *row;
  uint dirty;
  char *filename;
  char statusmsg[80];
  time_t statusmsg_time;
} Editor;

void init_editor(Editor *editor);
