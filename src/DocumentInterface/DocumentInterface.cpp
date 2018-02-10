#include "include/DocumentInterface.hpp"
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include <iostream>
#include "GUI/vt100/include/vt100terminal.hpp"

int DocumentInterface::fileCounter = 0;

DocumentInterface::DocumentInterface() {
  fileName = fileName + std::to_string(fileCounter) + ".txt";
  fileCounter += 1;
  fileHandler.open(fileName);
  gapBuff = new GapBuffer(100);
}

DocumentInterface::DocumentInterface(std::string fName):fileName(fName) {
  /*  fileHandler.open(fileName);
  gapBuff = new GapBuffer(100);
  char c;
  while(fileHandler.get(c)) {
    if(c=='\n') {
      gapBuff->Insert('\r');
      gapBuff->Insert('\n');
    } else {
      gapBuff->Insert(c);
    }
    }*/
}

DocumentInterface::~DocumentInterface() {
  fileCounter = fileCounter?fileCounter -= 1:0;
  fileHandler.close(); 
  delete gapBuff;
}

void DocumentInterface::NavigateBuffer(int cols, int rows) {
  //currently this implements only the left key
  gapBuff->MoveGap(cols);
}

void DocumentInterface::UpdateBuffer(int ch) {
  switch(ch) {
  case '\r':
    gapBuff->Insert('\n');
    gapBuff->Insert('\r');
    break;
  case KEYS::CODES::BACKSPACE:
    gapBuff->Backspace();
    break;
  default:
    gapBuff->Insert(ch);
    break;
  }
}

/*void DocumentInterface::OpenFileToBuffer(std::string fileName) {
  
  }*/

void DocumentInterface::SaveBufferToFile() {
  fileHandler<<gapBuff->printBuffer();
}

std::string DocumentInterface::printGapBuffer() {
  return gapBuff->printBuffer();
}
