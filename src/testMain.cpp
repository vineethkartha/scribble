#include<iostream>
//#include "DataStructures/include/DataStructureInterface.hpp"
#include "DocumentInterface/include/DocumentInterface.hpp"
#include "GUI/vt100/include/vt100terminal.hpp"
#include <string.h>
#include <fstream>

int main() {

  DocumentInterface *dp;
  VT100gui gui;
  int ch=0;
  bool cmdFlag = 0;
  std::string str;
  std::string ptr;
  gui.clearScreen();
  dp = new DocumentInterface();
  //gui.editorRefreshScreen(dp.getFileName(), dp.isDirtyState());
  gui.editorRefreshScreen("Open New File",false);
  while (ch != KEYS::CODES::EXIT_TERM) {
    ch = gui.VT100CommandProcess();    
    switch(ch) {
    case KEYS::CODES::UP_ARROW:
    case KEYS::CODES::DOWN_ARROW:
    case KEYS::CODES::LEFT_ARROW: 
    case KEYS::CODES::RIGHT_ARROW:
      dp->NavigateBuffer(gui.getColumn(),gui.getRow());
      break;
    case KEYS::CODES::OPEN_DOC:
      delete dp;
      str = gui.commandInputs();
      dp = new DocumentInterface(str);
      break;
    case KEYS::CODES::EXIT_TERM:
      break;
    case KEYS::CODES::SAVE_DOC:
      if(!dp->getFileNameisSet()) {
	cmdFlag = 1;
	str = gui.commandInputs();
	dp->SaveBufferToFile(str);
      } else {
	dp->SaveBufferToFile();
      }
      
      gui.DrawCursor(gui.getRow(), gui.getColumn());
      break;
    case '\r':
      cmdFlag = 0;
    case KEYS::CODES::BACKSPACE:
    default:
      cmdFlag = 0;
      dp->UpdateBuffer(ch);
      break;
    }
    if(!cmdFlag) {
      gui.editorRefreshScreen(dp->getFileName(), dp->isDirtyState());
      ptr = dp->printGapBuffer();
      gui.writeContent(ptr);
    }
  }
  gui.clearScreen();
  delete dp;
  return 0;
}
