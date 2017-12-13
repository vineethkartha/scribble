#include<iostream>
#include "include/GapBuffer.hpp"
#include "guilib.hpp"
/*
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

#include<iostream>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;


void termEnd(const char *s) {
  //write(STDOUT_FILENO, "\x1b[2J", 4);
  //write(STDOUT_FILENO, "\x1b[H", 3);
  perror(s);
  exit(1);
}


void revertToNormalMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    termEnd("tcsetattr");
}

void startRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    termEnd("tcgetattr");
  atexit(revertToNormalMode);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  //raw.c_cc[VMIN] = 0;
  //raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
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
    //if (nread == -1 && errno != EAGAIN) termEnd("read");
  }
  return c;
}


void editorProcessKeypress() {
  char c = editorReadKey();
  char *pc = &c;
  //std::string str(c);
  switch (c) {
  case CTRL_KEY('q'):
    revertToNormalMode();
    exit(0);
    break;
  default:
    write(STDOUT_FILENO, pc,1);
    break;
  }
}
*/

int main() {
   GapBuffer gp(2);
   VT100gui gui;
   //startRawMode();

while (1) {
char c = gui.editorReadKey();
char *pc = &c;
switch (c) {
 case CTRL_KEY('q'):
   //revertToNormalMode();
goto EXIT_POINT;
break;
 default:
gp.Insert(c);
write(STDOUT_FILENO, pc,1);
break;
}
//editorRefreshScreen();
}
EXIT_POINT:
std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";
//editorProcessKeypress();

  /*
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.Insert('e');
  gp.Debugprint();

  gp.MoveGap(1);
  gp.Delete();
  //gp.Insert('i');
  gp.Debugprint();

  gp.MoveGap(14);
  gp.Insert('e');
  gp.Insert('t');
  
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";
  */
return 0;
}
