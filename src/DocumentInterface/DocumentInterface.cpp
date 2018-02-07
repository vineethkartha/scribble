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
  std::cout<<fileName; // debug statement
}

DocumentInterface::~DocumentInterface() {
  fileCounter = fileCounter?fileCounter -= 1:0;
  fileHandler.close();
}

void DocumentInterface::NavigateBuffer(int cols, int rows) {
  gapBuff->MoveGap(--cols);
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

std::string DocumentInterface::printGapBuffer() {
  return gapBuff->printBuffer();
}
