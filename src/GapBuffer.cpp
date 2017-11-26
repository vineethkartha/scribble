#include "include/GapBuffer.hpp"
#include <algorithm>
#include<iostream>
GapBuffer::GapBuffer(int gapSize) {
  this->insertCounter = 0;
  this->buffer = new char[this->gapSize];
  this->bufferStart = this->buffer;
  this->gapStart = this->buffer;
  this->gapEnd = this->gapStart + this->gapSize;
  this->bufferEnd = this->bufferStart + this->gapSize;
}

GapBuffer::~GapBuffer() {
  delete(this->buffer);
}

char* GapBuffer::addChar(char c) {
  *(this->gapStart) = c;
  this->gapStart++;
  this->insertCounter += 1;
  return this->gapStart;
}


void GapBuffer::MoveGap(char *pointer) {
  // assuming that the pointer is moved backwards
  int sizetoMove = this->gapStart - pointer;
  auto newPointer = this->bufferEnd -sizetoMove;
  std::copy(pointer, pointer + sizetoMove, newPointer);
  this->gapStart = pointer;
  this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter);
}

void GapBuffer::printBuffer() {
  for(auto p = this->bufferStart; p <= this->bufferEnd; ++p) {

    if(p == this->gapStart) 
      std::cout<<"Contents of gap ==========\n";
    if(p == this->gapEnd)
      std::cout<<"Gap Ended============\n";
    
    std::cout<<*p;
  }
}


