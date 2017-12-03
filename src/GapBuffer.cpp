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
  // If the pointer is between the current position and
  // the gap end we should not move.
  bool NeedtoMove = !(pointer >= this->cursorPos
		      && pointer <= this->gapEnd);
  bool MoveForward = (pointer > this->cursorPos);

  if(NeedtoMove) {
    if(MoveForward) {
      //this->MoveGapForward(pointer);
      int sizetoMove = pointer -this->gapEnd;
      auto pointerToMove = this->gapEnd;
      std::copy(pointerToMove, pointerToMove + sizetoMove, this->cursorPos);
      this->cursorPos = this->cursorPos + sizetoMove; // this is not same as the pointer because of gapsize
    } else {
      //this->MoveGapBackward(pointer);
      int sizetoMove = this->cursorPos - pointer;
      auto pointerToMove = this->gapEnd -sizetoMove;
      std::copy(pointer, pointer + (sizetoMove), pointerToMove);
      this->cursorPos = pointer;
    }
    this->gapStart =this->cursorPos;
    this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter);
    // Clear the gap
    for(auto p = this->gapStart; p < this->gapEnd; ++p)
      *p ='\0';
  }
}
/* xxx TODO TO Be deleted 
void GapBuffer::MoveGapForward(char *pointer) {
  
  // assuming that the pointer is moved forwards
  // Handle exceptions
  if(pointer >= this->cursorPos && pointer <= this->gapEnd) {
    return;
  }
  int sizetoMove = pointer -this->gapEnd;
  auto pointerToMove = this->gapEnd;
  std::copy(pointerToMove, pointerToMove + sizetoMove, this->cursorPos);
  this->cursorPos = this->cursorPos + sizetoMove;
  this->gapStart = this->cursorPos;
  this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter);
  //auto newPointer = this->gapEnd -sizetoMove;
  for(auto p = this->gapStart; p < this->gapEnd; ++p)
    *p ='\0';
}
void GapBuffer::MoveGapBackward(char *pointer) {
  
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
*/

// THis is a debug print
void GapBuffer::Debugprint() {
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

std::string GapBuffer::printBuffer() {
  std::string buff;
  for(auto p = this->bufferStart; p<=this->bufferEnd; ++p) {
    //std::cout<<*p;
    if(*p != '\0')
      buff +=*p;
  }
  //buff += '\0';
  return buff;
}

