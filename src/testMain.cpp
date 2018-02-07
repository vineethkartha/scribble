#include<iostream>
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include "DocumentInterface/include/DocumentInterface.hpp"
#include "GUI/vt100/include/vt100terminal.hpp"
#include <string.h>
#include <fstream>

int main() {
  GapBuffer gp(20);
  DocumentInterface dp;
  DocumentInterface dp1;
  VT100gui gui;
  std::ofstream myfile;
  myfile.open("untitled.txt");
  int ch=0;
  int rows, cols;
  std::string ptr;
  while (ch != KEYS::CODES::EXIT_TERM) {
    ch = gui.VT100CommandProcess();
    gui.getCursorPosition(&rows,&cols);

    switch(ch) {
    case KEYS::CODES::UP_ARROW:
      break;
    case KEYS::CODES::DOWN_ARROW:
    case KEYS::CODES::LEFT_ARROW: 
      gp.MoveGap(--cols);
      //write(STDOUT_FILENO, ptr.c_str(),ptr.size());
      break;
    case KEYS::CODES::RIGHT_ARROW:
      break;
    case KEYS::CODES::EXIT_TERM:
      break;
      case KEYS::CODES::SAVE_DOC:
	myfile<<gp.printBuffer();
	break;
    case '\r':
	gp.Insert('\n');
	gp.Insert('\r');
	break;
    case KEYS::CODES::BACKSPACE:
	gp.Backspace();
	ptr = gp.printBuffer();
	write(STDOUT_FILENO, ptr.c_str(),ptr.size());
	break;
    default:
	gp.Insert(ch);
	ptr = gp.printBuffer();
	write(STDOUT_FILENO, ptr.c_str(),ptr.size());
	break;
    }
    ptr = gp.printBuffer();
    //gui.statusBar(ptr, rows);
  }
  myfile.close();
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n"<<rows<<"\n"<<cols<<"\n";
  return 0;
}
