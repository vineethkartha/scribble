#include "include/DocumentInterface.hpp"
#include "DataStructures/include/DataStructureInterface.hpp"
#include <iostream>

int DocumentInterface::fileCounter = 0;

DocumentInterface::DocumentInterface() {
  fileName = "";
  fileCounter += 1;
  fileNameisSet = false;
  contentBuffer = DataStructureInterface::CreateDS(1);
  dirtyFlag = 0;
}

DocumentInterface::DocumentInterface(std::string fName):fileName(fName) {
  fileHandler.open(fileName, std::fstream::in | std::fstream::out);
  contentBuffer = DataStructureInterface::CreateDS(1);
  char c;
  while(fileHandler.get(c)) {
    if(c=='\n') {
      contentBuffer->Insert('\r');
      contentBuffer->Insert('\n');
    } else {
      contentBuffer->Insert(c);
    }
  }
  fileNameisSet = true;
  fileHandler.close();
}

DocumentInterface::~DocumentInterface() {
  fileCounter = fileCounter?fileCounter -= 1:0;
  fileHandler.close();
  delete contentBuffer;
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
  contentBuffer->MoveCursor(cols);
}

void DocumentInterface::UpdateBuffer(int ch) {
  switch(ch) {
  case '\r':
    contentBuffer->Insert('\n');
    contentBuffer->Insert('\r');
    dirtyFlag++;
    break;
  default:
    contentBuffer->Insert(ch);
    dirtyFlag++;
    break;
  }
}

void DocumentInterface::BackSpaceBuffer() {
  contentBuffer->Backspace();
  dirtyFlag++;
}
void DocumentInterface::SaveBufferToFile(std::string fName) {
  if(!fileHandler.is_open()) {
    fileName = fName;
    fileHandler.open(fName, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if(!fileHandler.is_open()) {
      std::cout<<"File could not be saved \n";
    }
    fileNameisSet = true;
  }
  fileHandler<<contentBuffer->getContentOfBuffer();
  fileHandler.close();
  dirtyFlag = 0;
}

std::string DocumentInterface::printGapBuffer() {
  return contentBuffer->getContentOfBuffer();
}
