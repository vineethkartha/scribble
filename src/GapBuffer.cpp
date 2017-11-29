#include "include/GapBuffer.hpp"
#include <algorithm>
#include<iostream>
GapBuffer::GapBuffer(int gapSize) {
  this->insertCounter = 0;
  this->gapSize = gapSize;
  this->buffer = new char[this->gapSize];
  this->bufferStart = this->buffer;
  this->cursorPos = this->bufferStart;
  this->gapStart = this->buffer;
  this->gapEnd = this->gapStart + this->gapSize;
  this->bufferEnd = this->bufferStart + this->gapSize;
}

/* implement the cons with a file input
GapBuffer::GapBuffer(FILE *fileH) {
}*/

GapBuffer::~GapBuffer() {
  delete(this->buffer);
}

char* GapBuffer::addChar(char c) {
  *(this->cursorPos) = c;
  this->cursorPos++;
  this->insertCounter += 1;
  return this->cursorPos;
}


void GapBuffer::MoveGap(int pos) {
  auto pointer = this->bufferStart + pos;
  // assuming that the pointer is moved backwards
  int sizetoMove = this->cursorPos - pointer;
  auto newPointer = this->gapEnd -sizetoMove;
  std::copy(pointer, pointer + (sizetoMove), newPointer);
  this->gapStart = pointer;
  this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter);
  // Clear the gap
  for(auto p = this->gapStart; p < this->gapEnd; ++p)
    *p ='\0';
  this->cursorPos = this->gapStart;
  }

void GapBuffer::printBuffer() {
  for(auto p = this->bufferStart; p <= this->bufferEnd; ++p) {

    if(p == this->gapStart) 
      std::cout<<"\nContents of gap ==========\n";
    if(p == this->gapEnd) 
      std::cout<<"\nGap Ended============\n";
    if(*p == '\0' && p!=this->bufferEnd)
      std::cout<<"_";
    std::cout<<*p;
  }
  std::cout<<"\n";
}


