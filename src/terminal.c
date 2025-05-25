#include "terminal.h"
#include "string.h"

Terminal terminal;

/* Init terminal */
void init_terminal() {
  enable_raw_mode();
  atexit(disable_raw_mode);
}

void print_termios_flags(struct termios *term) {
  // Input flags (c_iflag)
  printf("> Input flags (c_iflag):\n");
  printf("BRKINT: %s.\n", (term->c_iflag & BRKINT) ? "ON" : "OFF");
  printf("ICRNL: %s.\n", (term->c_iflag & ICRNL) ? "ON" : "OFF");
  printf("IGNBRK: %s.\n", (term->c_iflag & IGNBRK) ? "ON" : "OFF");
  printf("IGNCR: %s.\n", (term->c_iflag & IGNCR) ? "ON" : "OFF");
  printf("IGNPAR: %s.\n", (term->c_iflag & IGNPAR) ? "ON" : "OFF");
  printf("INLCR: %s.\n", (term->c_iflag & INLCR) ? "ON" : "OFF");
  printf("INPCK: %s.\n", (term->c_iflag & INPCK) ? "ON" : "OFF");
  printf("ISTRIP: %s.\n", (term->c_iflag & ISTRIP) ? "ON" : "OFF");
  printf("IXANY: %s.\n", (term->c_iflag & IXANY) ? "ON" : "OFF");
  printf("IXOFF: %s.\n", (term->c_iflag & IXOFF) ? "ON" : "OFF");
  printf("IXON: %s.\n", (term->c_iflag & IXON) ? "ON" : "OFF");
  printf("PARMRK: %s.\n", (term->c_iflag & PARMRK) ? "ON" : "OFF");

  // Output flags (c_oflag)
  printf("> Output flags (c_oflag):\n");
  printf("OPOST: %s.\n", (term->c_oflag & OPOST) ? "ON" : "OFF");
  printf("ONLCR: %s.\n", (term->c_oflag & ONLCR) ? "ON" : "OFF");
  printf("OCRNL: %s.\n", (term->c_oflag & OCRNL) ? "ON" : "OFF");
  printf("ONOCR: %s.\n", (term->c_oflag & ONOCR) ? "ON" : "OFF");
  printf("ONLRET: %s.\n", (term->c_oflag & ONLRET) ? "ON" : "OFF");
  printf("OFDEL: %s.\n", (term->c_oflag & OFDEL) ? "ON" : "OFF");
  printf("OFILL: %s.\n", (term->c_oflag & OFILL) ? "ON" : "OFF");
  // TODO: Reports error as "undeclared"
  // printf("NLDLY: %s.\n", (term->c_oflag & NLDLY) ? "ON" : "OFF");
  // printf("CRDLY: %s.\n", (term->c_oflag & CRDLY) ? "ON" : "OFF");
  // printf("TABDLY: %s.\n", (term->c_oflag & TABDLY) ? "ON" : "OFF");
  // printf("BSDLY: %s.\n", (term->c_oflag & BSDLY) ? "ON" : "OFF");
  printf("VTDLY: %s.\n", (term->c_oflag & VTDLY) ? "ON" : "OFF");
  // printf("FFDLY: %s.\n", (term->c_oflag & FFDLY) ? "ON" : "OFF");

  // Control flags (c_cflag)
  printf("> Control flags (c_cflag):\n");
  printf("CSIZE: %s.\n", (term->c_cflag & CSIZE) ? "ON" : "OFF");
  printf("CSTOPB: %s.\n", (term->c_cflag & CSTOPB) ? "ON" : "OFF");
  printf("CREAD: %s.\n", (term->c_cflag & CREAD) ? "ON" : "OFF");
  printf("PARENB: %s.\n", (term->c_cflag & PARENB) ? "ON" : "OFF");
  printf("PARODD: %s.\n", (term->c_cflag & PARODD) ? "ON" : "OFF");
  printf("HUPCL: %s.\n", (term->c_cflag & HUPCL) ? "ON" : "OFF");
  printf("Flag CLOCAL: %s.\n", (term->c_cflag & CLOCAL) ? "ON" : "OFF");

  // Local flags (c_lflag)
  printf("> Local flags (c_lflag):\n");
  printf("ECHO: %s.\n", (term->c_lflag & ECHO) ? "ON" : "OFF");
  printf("ECHOE: %s.\n", (term->c_lflag & ECHOE) ? "ON" : "OFF");
  printf("ECHOK: %s.\n", (term->c_lflag & ECHOK) ? "ON" : "OFF");
  printf("ECHONL: %s.\n", (term->c_lflag & ECHONL) ? "ON" : "OFF");
  printf("ICANON: %s.\n", (term->c_lflag & ICANON) ? "ON" : "OFF");
  printf("IEXTEN: %s.\n", (term->c_lflag & IEXTEN) ? "ON" : "OFF");
  printf("ISIG: %s.\n", (term->c_lflag & ISIG) ? "ON" : "OFF");
  printf("NOFLSH: %s.\n", (term->c_lflag & NOFLSH) ? "ON" : "OFF");
  printf("TOSTOP: %s.\n", (term->c_lflag & TOSTOP) ? "ON" : "OFF");
}

/* Enable terminal raw mode */
void enable_raw_mode() {
  // Get terminal parameters and store them into a termios structure
  if (tcgetattr(STDIN_FILENO, &terminal.orig_termios) == -1) {
    die("tcgetattr");
  }

  // Put original termios parameters into ram termios
  terminal.raw_termios = terminal.orig_termios;

  // Edit terminal parameters from raw termios
  // https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/termios.h.html
  terminal.raw_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  terminal.raw_termios.c_oflag &= ~(OPOST);
  terminal.raw_termios.c_cflag |= (CS8);
  terminal.raw_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  terminal.raw_termios.c_cc[VMIN] = 0;
  terminal.raw_termios.c_cc[VTIME] = 1;

  // Set terminal parameters from termios structure
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal.raw_termios) == -1) {
    die("tcsetattr");
  }
}

/* Disable terminal raw mode */
void disable_raw_mode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal.orig_termios) == -1) {
    die("tcsetattr");
  }
}

/* This function makes a system call with ioctl()
    to get the windows size (number of rows and cols).
    On success zero is returned.
    On error, -1 is returned, and errno is set to indicate
    the error. */
int get_window_size(uint *rows, uint *cols) {
  // TIOCGWINSZ is a device-dependent operation code to get window size
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal.ws) == -1 ||
      terminal.ws.ws_col == 0) {
    // TODO: ioctl() won't be able to request the window size on all systems
    // so you might extend a cursor moving strategy here.
    // Check viewsourcecode.org/snaptoken/kilo
    return -1;
  } else {
    *cols = terminal.ws.ws_col;
    *rows = terminal.ws.ws_row;
    return 0;
  }
}

/* This function prints the last error encountered
    and terminates the execution of the program.
    perror prints the "human readable" error message
    associated with errno's value. */
void die(const char *message) {
  perror(message);
  exit(EXIT_FAILURE);
}
