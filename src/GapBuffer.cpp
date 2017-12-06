#include "include/GapBuffer.hpp"
#include <algorithm>
#include <iostream>

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
void GapBuffer::ResizeBuffer() {

  if(this->gapStart < this->gapEnd -1)
    return;
  unsigned int size = this->gapSize * 2;
  char *tempBuffer = new char[size];
  std::copy(this->bufferStart, this->bufferEnd, tempBuffer);
  auto cursorPos = this->cursorPos - this->bufferStart;
  auto origSize = this->bufferEnd - this->bufferStart;
  delete(this->buffer);
  this->buffer = tempBuffer;
  this->bufferStart = tempBuffer;
  this->bufferEnd = this->bufferStart + size;
  this->cursorPos = this->bufferStart + cursorPos;
  this->gapStart = this->bufferStart + origSize;
  this->gapEnd = this->bufferEnd;
  this->gapSize = size;
  this->MoveGap(cursorPos);
}

char* GapBuffer::Insert(char c) {
  this->ResizeBuffer();
  *(this->cursorPos) = c;
  if(this->cursorPos < (this->bufferEnd - 1)) {
    this->cursorPos++;
    this->gapStart++;
  }
  this->insertCounter += 1;
  return this->cursorPos;
}
// In the example shown below the cursor is on E
// that is why the gap is before E
// abcd[  ]Efgh
void GapBuffer::Delete() {
  if(this->gapEnd == this->bufferEnd)
    return;
  *(this->gapEnd) ='\0';
  this->gapEnd++;
}

void GapBuffer::Backspace() {
  if(this->cursorPos == this->bufferStart)
    return;
  this->cursorPos--;
  *(this->cursorPos) = '\0';
  this->gapStart--;
  this->insertCounter -=1;
}

void GapBuffer::MoveGap(int pos) {
  auto pointer = this->bufferStart + pos;
  // If the pointer is between the current position and
  // the gap end we should not move.
  if(pointer < this->bufferStart ||
     pointer > this->bufferEnd)
    return;
  bool NeedtoMove = !(pointer >= this->cursorPos
		      && pointer <= this->gapEnd + 1);
  bool MoveForward = (pointer > this->cursorPos);

  if(NeedtoMove) {
    if(MoveForward) {
      //this->MoveGapForward(pointer);
      int sizetoMove = pointer - this->gapEnd;
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
    this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter - 1);
    // Clear the gap
    for(auto p = this->gapStart; p <= this->gapEnd; ++p)
      *p ='\0';
    *(this->bufferEnd + 1) = '\0'; 
  }
}

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
  int c =0;
  for(auto ptr = this->bufferStart; ptr < this->bufferEnd; ++ptr) {
    c++;
    // Skip the gap this should be empty.
    if(ptr >= this->gapStart &&
       ptr <= this->gapEnd)
      continue;
    //std::cout<<*ptr;
    
    buff +=*ptr;
  }
  //std::cout<<c<<"\n";
  return buff;
}

