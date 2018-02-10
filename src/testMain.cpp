#include<iostream>
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include "DocumentInterface/include/DocumentInterface.hpp"
#include "GUI/vt100/include/vt100terminal.hpp"
#include <string.h>
#include <fstream>

int main() {
  GapBuffer gp(20);
  //DocumentInterface dp("test.txt");
  DocumentInterface dp;
  VT100gui gui;
  int ch=0;
  std::string ptr;
  gui.clearScreen();
  
  while (ch != KEYS::CODES::EXIT_TERM) {
    ch = gui.VT100CommandProcess();    
    switch(ch) {
    case KEYS::CODES::UP_ARROW:
    case KEYS::CODES::DOWN_ARROW:
    case KEYS::CODES::LEFT_ARROW: 
    case KEYS::CODES::RIGHT_ARROW:
      dp.NavigateBuffer(gui.getColumn(),gui.getRow());
      break;
    case KEYS::CODES::OPEN_DOC:
      break;
    case KEYS::CODES::EXIT_TERM:
      gui.clearScreen();
      break;
    case KEYS::CODES::SAVE_DOC:
      dp.SaveBufferToFile();
      break;
      
    case KEYS::CODES::BACKSPACE:
    default:
      gui.clearScreen();
      dp.UpdateBuffer(ch);
      ptr = dp.printGapBuffer();
      write(STDOUT_FILENO, ptr.c_str(),ptr.size());
      //gui.editorRefreshScreen();
      
      break;
      }
    //ptr = dp.printGapBuffer();
    //write(STDOUT_FILENO, ptr.c_str(),ptr.size());
    //gui.statusBar(ptr, rows);
  }
  return 0;
}
