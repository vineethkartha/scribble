#include<iostream>
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include "DocumentInterface/include/DocumentInterface.hpp"
#include "GUI/vt100/include/vt100terminal.hpp"
#include <string.h>
#include <fstream>

int main() {
  GapBuffer gp(20);
  DocumentInterface dp;

  VT100gui gui;
  int ch=0;
  int rows, cols;
  std::string ptr;
  while (ch != KEYS::CODES::EXIT_TERM) {
    ch = gui.VT100CommandProcess();
    gui.getCursorPosition(&rows,&cols);

    switch(ch) {
    case KEYS::CODES::UP_ARROW:
    case KEYS::CODES::DOWN_ARROW:
    case KEYS::CODES::LEFT_ARROW: 
    case KEYS::CODES::RIGHT_ARROW:
      dp.NavigateBuffer(ch,cols);
      break;
    case KEYS::CODES::EXIT_TERM:
    case KEYS::CODES::SAVE_DOC:
      dp.UpdateBuffer(ch);
      break;
    case KEYS::CODES::BACKSPACE:
    default:
      dp.UpdateBuffer(ch);
      ptr = dp.printGapBuffer();
      write(STDOUT_FILENO, ptr.c_str(),ptr.size());
      break;
    }
    ptr = dp.printGapBuffer();
    write(STDOUT_FILENO, ptr.c_str(),ptr.size());
    //gui.statusBar(ptr, rows);
  }
  return 0;
}
