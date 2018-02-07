#include "include/vt100terminal.hpp"
#include <string.h>
#include <termios.h>
#include<iostream>
#include <sys/ioctl.h>

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
  getWinSize();
}

void VT100gui::getWinSize() {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return;
  } else {
    rowSize = ws.ws_col;
    colSize = ws.ws_row;
  }
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


int VT100gui::ReadKey() {
  int nread;
  char readChar;
  while ((nread = read(STDIN_FILENO, &readChar, 1)) != 1);
  if('\x1b' == readChar) {
    char escapeSeq[3];
    read(STDIN_FILENO, escapeSeq, 2);
    if ('[' == escapeSeq[0]) {
      switch (escapeSeq[1]) {
      case 'A': return KEYS::CODES::UP_ARROW;
      case 'B': return KEYS::CODES::DOWN_ARROW;
      case 'C': return KEYS::CODES::RIGHT_ARROW;
      case 'D': return KEYS::CODES::LEFT_ARROW;
      }
    }
    return '\x1b';
  } 
  return readChar;
}


int VT100gui::VT100CommandProcess() {
  int key = ReadKey();
  int rows, cols;
  getCursorPosition(&rows, &cols);
  switch (key) {
      
  case KEYS::CODES::EXIT_TERM:
    return KEYS::CODES::EXIT_TERM;
    
  case KEYS::CODES::SAVE_DOC:
    return KEYS::CODES::SAVE_DOC;
    
  case KEYS::CODES::UP_ARROW:
    {
      char buf[10];
      rows--;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,cols);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::UP_ARROW;
    }

  case KEYS::CODES::DOWN_ARROW:
    {
      char buf[10];
      rows++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,cols);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::DOWN_ARROW;
    }

  case KEYS::CODES::RIGHT_ARROW:
    {
      char buf[10];
      cols++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,cols);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::RIGHT_ARROW;
    }
  case KEYS::CODES::LEFT_ARROW:
    {
      char buf[10];
      cols--;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,cols);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::LEFT_ARROW;
    }
  case '\r':
    {
      char buf[15];
      rows++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,1);
      write(STDOUT_FILENO,buf,strlen(buf));
      return '\r';
    }
  case KEYS::CODES::BACKSPACE:
      cols--;      
      write(STDOUT_FILENO, "\x1b[J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      return KEYS::CODES::BACKSPACE;
  default:
      write(STDOUT_FILENO, "\x1b[1J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      return key;
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

void VT100gui::statusBar(std::string ptr, int rows) {


  char buf[15];
  write(STDOUT_FILENO, ptr.c_str(),ptr.size());
  write(STDOUT_FILENO, "\x1b[7m", 4);

  // rest of code here
  char status[80];
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rowSize,1);
  write(STDOUT_FILENO,buf,strlen(buf));
  snprintf(status, sizeof(status), "%.20s - %d lines",
    "untitled", rows);
  write(STDOUT_FILENO, status, 20);
  write(STDOUT_FILENO, "\x1b[m", 3);

  //  abAppend(ab, "\x1b[m", 3);
}
