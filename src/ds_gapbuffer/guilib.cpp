#include <termios.h>
#include "guilib.hpp"
#include<iostream>

// Global variable with the default terminal settings
//struct termios orig_termios;

VT100gui::VT100gui() {
  //struct termios orig_termios;
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    exitException("tcgetattr");
  //atexit(revertToNormalMode);
  
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  //raw.c_cc[VMIN] = 0;
  //raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

VT100gui::~VT100gui() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    exitException("tcsetattr");
}

void VT100gui::exitException(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  perror(s);
  exit(1);
}


/*
void VT100gui::startRawMode() {
  //struct termios orig_termios;
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    exitException("tcgetattr");
  atexit(revertToNormalMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  //raw.c_cc[VMIN] = 0;
  //raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
*/
void VT100gui::editorDrawRows() {
  int y;
  for (y = 0; y < 24; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void VT100gui::editorRefreshScreen() {
  //write(STDOUT_FILENO, "\x1b[2J", 4);
  //write(STDOUT_FILENO, "\x1b[H", 3);
  //editorDrawRows();
  //write(STDOUT_FILENO, "\x1b[H", 3);
}


char VT100gui::editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    //if (nread == -1 && errno != EAGAIN) exitException("read");
  }
  return c;
}

/*
void VT100gui::editorProcessKeypress() {
  char c = editorReadKey();
  char *pc = &c;
  //std::string str(c);
  switch (c) {
  case CTRL_KEY('q'):
    exit(0);
    break;
  default:
    write(STDOUT_FILENO, pc,1);
    break;
  }
}
*/
/*int main() {
  enableRawMode();
  
  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
  }*/
