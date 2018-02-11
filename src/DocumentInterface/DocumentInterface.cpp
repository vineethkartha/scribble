#include "include/DocumentInterface.hpp"
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include <iostream>
#include "GUI/vt100/include/vt100terminal.hpp"

int DocumentInterface::fileCounter = 0;

DocumentInterface::DocumentInterface() {
  fileName = "";
  fileCounter += 1;
  fileNameisSet = false;
  gapBuff = new GapBuffer(100);
  dirtyFlag = 0;
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

std::string DocumentInterface::getFileName() const {
  if(fileName == "") {
    return("untitled" + std::to_string(fileCounter) + ".txt");
  }
  return fileName;
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
    dirtyFlag++;
    break;
  case KEYS::CODES::BACKSPACE:
    gapBuff->Backspace();
    dirtyFlag++;
    break;
  default:
    gapBuff->Insert(ch);
    dirtyFlag++;
    break;
  }
}

bool DocumentInterface::isDirtyState() const {
  return dirtyFlag;
}

/*void DocumentInterface::OpenFileToBuffer(std::string fileName) {
  
  }*/

void DocumentInterface::SaveBufferToFile(std::string fName) {
  if(!fileHandler.is_open()) {
    fileName = fName;
    fileHandler.open(fName);
    fileNameisSet = true;
  }
  fileHandler<<gapBuff->printBuffer();
  dirtyFlag = 0;
}

bool DocumentInterface::getFileNameisSet() const {
  return fileNameisSet;
}
std::string DocumentInterface::printGapBuffer() {
  return gapBuff->printBuffer();
}
