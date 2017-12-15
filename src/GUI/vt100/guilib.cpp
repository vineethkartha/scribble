#include "include/guilib.hpp"

#include <termios.h>
#include<iostream>


VT100gui::VT100gui() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    exitonException("tcgetattr");
  
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
    exitonException("tcsetattr");
}

void VT100gui::exitonException(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  perror(s);
  exit(1);
}

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
    //if (nread == -1 && errno != EAGAIN) exitonException("read");
  }
  if(c== '\x1b')
    {
      char seq[3];
      read(STDIN_FILENO, seq, 3);
      //read(STDIN_FILENO, &seq[1], 1);
      if (seq[0] == '[') {
	switch (seq[1]) {
	case 'A':
	  //write(STDOUT_FILENO, "Hello", 5);
	  return 'A';
	  /*
	    case 'B': return 's';
	    case 'C': return 'd';
	    case 'D': return 'a';
	  */
	}
      }
      return '\x1b';
    }else {
    return c;
  }
  return c;
}


void VT100gui::editorProcessKeypress() {
  char c = editorReadKey();
  char *pc = &c;
  switch (c) {
  case CTRL_KEY('q'):
    //goto EXIT_POINT;
    break;
  case 'A':
    {
      write(STDOUT_FILENO, "Hello", 5);
      break;
    }
  case 127:
    //write(STDOUT_FILENO, "\x1b[H", 3);
    //gp.Backspace();
    break;
  default:
    //std::cout<<c<<"\n";
    //printf("(%d) %c\n",c,c);
    //gp.Insert(c);
    write(STDOUT_FILENO, pc,1);
    break;
  }
}

int VT100gui::getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';
  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
  return 0;
}
/*int main() {
  enableRawMode();
  
  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
  }*/
