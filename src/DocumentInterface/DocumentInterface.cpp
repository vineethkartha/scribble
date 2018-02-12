#include "include/DocumentInterface.hpp"
#include "DataStructures/include/DataStructureInterface.hpp"
//#include "gapbuffer/include/GapBuffer.hpp"
#include <iostream>
#include "GUI/vt100/include/vt100terminal.hpp"

int DocumentInterface::fileCounter = 0;

DocumentInterface::DocumentInterface() {
  fileName = "";
  fileCounter += 1;
  fileNameisSet = false;
  gapBuff = DataStructureInterface::CreateDS(1);
  dirtyFlag = 0;
}

DocumentInterface::DocumentInterface(std::string fName):fileName(fName) {
  fileHandler.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
  gapBuff = DataStructureInterface::CreateDS(1);
  char c;
  while(fileHandler.get(c)) {
    if(c=='\n') {
      gapBuff->Insert('\r');
      gapBuff->Insert('\n');
    } else {
      gapBuff->Insert(c);
    }
  }
  fileNameisSet = true;
}

DocumentInterface::~DocumentInterface() {
  fileCounter = fileCounter?fileCounter -= 1:0;
  fileHandler.close(); 
  delete gapBuff;
}

std::string DocumentInterface::getFileName() const {
  if(fileName == "") {
    return("untitled" + std::to_string(fileCounter) + ".txt");
  }
  return fileName;
}

bool DocumentInterface::isDirtyState() const {
  return dirtyFlag;
}

bool DocumentInterface::getFileNameisSet() const {
  return fileNameisSet;
}

void DocumentInterface::NavigateBuffer(int cols, int rows) {
  //currently this implements only the left key
  gapBuff->MoveCursor(cols);
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

void DocumentInterface::SaveBufferToFile(std::string fName) {
  if(!fileHandler.is_open()) {
    fileName = fName;
    fileHandler.open(fName, std::fstream::in | std::fstream::out | std::fstream::app);
    fileNameisSet = true;
  }
  fileHandler<<gapBuff->getContentOfBuffer();
  dirtyFlag = 0;
}

std::string DocumentInterface::printGapBuffer() {
  return gapBuff->getContentOfBuffer();
}
