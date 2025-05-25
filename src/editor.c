#include "editor.h"
#include "terminal.h"

/* This function initialize the editor with the
    default values. */
void init_editor(Editor *editor) {
  // Init terminal
  init_terminal();

  // Set default values
  editor->cx = 0;
  editor->cy = 0;
  editor->rx = 0;
  editor->rowoff = 0;
  editor->coloff = 0;
  editor->numrows = 0;
  editor->row = NULL;
  editor->dirty = 0;
  editor->filename = NULL;
  editor->statusmsg[0] = '\0';
  editor->statusmsg_time = 0;

  // Get window size
  if (get_window_size(&editor->screenrows, &editor->screencols) == -1) {
    die("get_window_size");
  }

  // Subtract two from the screen rows, because they are used
  // for editor layout.
  editor->screenrows -= 2;
}
