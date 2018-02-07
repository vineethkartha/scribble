#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

//#include<iostream>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;


void revertToNormalMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    terminate("tcsetattr");
}

void startRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    terminate("tcgetattr");
  atexit(disableRawMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  //raw.c_cc[VMIN] = 0;
  //raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void terminate(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  perror(s);
  exit(1);
}

void editorDrawRows() {
  int y;
  for (y = 0; y < 24; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void editorRefreshScreen() {
  //write(STDOUT_FILENO, "\x1b[2J", 4);
  //write(STDOUT_FILENO, "\x1b[H", 3);
  //editorDrawRows();
  //write(STDOUT_FILENO, "\x1b[H", 3);
}


char editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

/*** input ***/
void editorProcessKeypress() {
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

int main() {
  enableRawMode();
  
  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}
