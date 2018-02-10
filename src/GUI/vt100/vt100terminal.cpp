#include "include/vt100terminal.hpp"
#include <string.h>
#include <termios.h>
#include<iostream>
#include <sys/ioctl.h>
#include <assert.h>
void VT100gui::CommandWriterHelper(const std::string command) {
  char buf[32];
  snprintf(buf, sizeof(buf), command.c_str(),0);
  write(STDOUT_FILENO,command.c_str(),command.length());
}

VT100gui::VT100gui() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
    exitonException("tcgetattr");
  
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
  getWinSize();
  currRow = 0;
  currCol = 0;
}

VT100gui::~VT100gui() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    exitonException("tcsetattr");
}

void VT100gui::clearScreen() {
  CommandWriterHelper("\x1b[2J\x1b[H");
}

void VT100gui::getWinSize() {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    assert(false);
    return;
  } else {
    numOfCols = ws.ws_col;
    numOfRows = ws.ws_row;
  }
}

void VT100gui::exitonException(const char *s) {
  CommandWriterHelper("\x1b[2J\x1b[H");
  perror(s);
  exit(1);
}

void VT100gui::editorDrawRows() {
  int y;
  for (y = 0; y < 24; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void VT100gui::editorRefreshScreen(std::string fName) {
  CommandWriterHelper("\x1b[K\x1b[H");
  statusBar(fName);
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
  getCursorPosition();
  switch (key) {
      
  case KEYS::CODES::EXIT_TERM:
    return KEYS::CODES::EXIT_TERM;
    
  case KEYS::CODES::SAVE_DOC:
    return KEYS::CODES::SAVE_DOC;
    
  case KEYS::CODES::UP_ARROW:
    {
      char buf[10];
      currRow--;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",currRow,currCol);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::UP_ARROW;
    }

  case KEYS::CODES::DOWN_ARROW:
    {
      char buf[10];
      currRow++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",currRow,currCol);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::DOWN_ARROW;
    }

  case KEYS::CODES::RIGHT_ARROW:
    {
      char buf[10];
      currCol++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",currRow,currCol);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::RIGHT_ARROW;
    }
  case KEYS::CODES::LEFT_ARROW:
    {
      char buf[10];
      currCol--;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",currRow,currCol);
      write(STDOUT_FILENO,buf,strlen(buf));
      return KEYS::CODES::LEFT_ARROW;
    }
  case '\r':
    {
      char buf[15];
      currRow++;
      snprintf(buf, sizeof(buf), "\x1b[%d;%dH",currRow,0);
      write(STDOUT_FILENO,buf,strlen(buf));
      return '\r';
    }
  case KEYS::CODES::BACKSPACE:
      currCol--;      
      write(STDOUT_FILENO, "\x1b[J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      return KEYS::CODES::BACKSPACE;
  default:
    write(STDOUT_FILENO, "\x1b[1J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    return key;
  }
  //  std::cout<<currRow<<":"<<currCol<<";";
}

int VT100gui::getCursorPosition() {
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
  if (sscanf(&buf[2], "%d;%d", &currRow, &currCol) != 2) {
    //    std::cout<<rows<<":"<<cols<<";";
    return -1;
  }
  return 0;
}
int VT100gui::getRow() const{
  return currRow;
}
int VT100gui::getColumn() const {
  return currCol;
}

void VT100gui::statusBar(std::string fName) {
  getWinSize();
  // take cursor to the last line of the screen
  std::string cmd = "\x1b["+std::to_string(numOfRows)+";0H"; 
  CommandWriterHelper(cmd);
  CommandWriterHelper("\x1b[7m");

  int len = 0;
  std::string statusMsg = fName + " Line:" + std::to_string(currRow);
  CommandWriterHelper(statusMsg);
  while (len < (numOfCols-statusMsg.length())) {
    CommandWriterHelper(" ");
    len++;
  }
  CommandWriterHelper("\x1b[m");
  CommandWriterHelper("\x1b[0;0H");
}
