#include "include/GapBuffer.hpp"
#include <algorithm>
#include <iostream>
#include <assert.h>

GapBuffer::GapBuffer(int gapSize) {
  this->insertCounter = 0;
  this->gapSize = gapSize;
  this->buffer = new char[this->gapSize];
  this->bufferStart = this->buffer;
  this->cursorPos = this->bufferStart;
  this->gapStart = this->buffer;
  this->gapEnd = this->gapStart + this->gapSize;
  this->bufferEnd = this->bufferStart + this->gapSize;
  for(auto p = this->bufferStart; p <= this->bufferEnd; ++p)
    *p ='\0';
}

GapBuffer::~GapBuffer() {
  delete(this->buffer); 
  bufferStart = nullptr;
  bufferEnd = nullptr;
  gapStart = nullptr;
  gapEnd = nullptr;
  cursorPos = nullptr;
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
  this->MoveCursor(cursorPos);
}

/**
 * @name Insert
 * This function inserts the symbol passed
 * and increments the gapStart and the cursorPos pointer.
 * Consider the text shown below with 4 blank spaces:
 * This is a gap buffer [----]
 *  			        ^
 * on inserting the character 'i'
 * The buffer will be as shown below:
 * This is a gap buffer i[---]
 *  			        ^			      
 */
void GapBuffer::Insert(char symbol) {
  this->ResizeBuffer();
  *(this->cursorPos) = symbol;
  if(this->cursorPos < (this->bufferEnd - 1)) {
    this->cursorPos++;
    this->gapStart++;
  }
  this->insertCounter += 1;
}

/**
 * @name Delete
 * This function deletes the character under the cursor
 * and increments the gapEnd pointer.
 * Consider the text shown below with the cursor under d:
 * This is a gap buffer [--]delete
 *  			      ^
 * The gap has 2 spaces left. After the delete operatio
 * The buffer will be as shown below:
 * This is a gap buffer [---]elete
 *  			     ^			      
 */
void GapBuffer::Delete() {
  if(this->gapEnd == this->bufferEnd)
    return;
  *(this->gapEnd) ='\0';
  this->gapEnd++;
}

/**
 * @name Backspace
 * This function deletes the character under the before
 * the cursor and decrements the gapStart pointer and
 * the cursorPos pointer.
 * Consider the text shown below with the cursor under b:
 * This is a gap buffer[--]backspace
 *  			     ^
 * without the gap the text would like like
 * This is a gap bufferbackspace
 *                     ^
 * After the backspace operation
 * The buffer will be as shown below:
 * This is a gap buffe[---]backspace
 *                         ^                    
 */
void GapBuffer::Backspace() {
  if(this->cursorPos == this->bufferStart)
    return;
  this->cursorPos--;
  *(this->cursorPos) = '\0';
  this->gapStart--;
  this->insertCounter -= 1;
}

void GapBuffer::MoveCursor(int pos) {
  auto pointer = this->bufferStart + pos;
  // If the pointer is between the current position and
  // the gap end we should not move.
  if(pointer < this->bufferStart ||
     pointer > this->bufferEnd)
    return;
  bool modifyPos = (pointer >= this->cursorPos
		    && pointer <= this->gapEnd + 1);
  bool MoveForward = (pointer > this->cursorPos);

  if(modifyPos && MoveForward) {
    pointer  = (this->gapEnd - this->cursorPos) + this->cursorPos + 1;
  }
  if(MoveForward) {
    int sizetoMove = pointer - this->gapEnd;
    auto pointerToMove = this->gapEnd;
    std::copy(pointerToMove, pointerToMove + sizetoMove, this->cursorPos);
    this->cursorPos = this->cursorPos + sizetoMove; // this is not same as the pointer because of gapsize
  } else {
    int sizetoMove = this->cursorPos - pointer;
    auto pointerToMove = this->gapEnd - sizetoMove;
    std::copy(pointer, pointer + (sizetoMove), pointerToMove);
    this->cursorPos = pointer;
  }
  this->gapStart =this->cursorPos;
  this->gapEnd = this->gapStart + (this->gapSize - this->insertCounter);
  // Clear the gap 
  for(auto p = this->gapStart; p < this->gapEnd; ++p)
    *p ='\0';
  *(this->bufferEnd) = '\0';
}

/**
 * @name printBuffer
 * This function returns the contents of the entire buffer as a string
 * It ignores the gap in between.
 */
std::string GapBuffer::getContentOfBuffer() const{
  std::string buff;
  for(auto ptr = this->bufferStart; ptr < this->bufferEnd; ++ptr) {
    // Skip the gap this should be empty.
    if(ptr >= this->gapStart &&
       ptr < this->gapEnd) {
      assert(*ptr == '\0');
      continue;
    }
    buff += *ptr;
  }
  return buff;
}


// THis is a debug print surround it with NDEBUG
void GapBuffer::Debugprint() {
  std::cout<<"\n Printing Start\n";
  for(auto p = this->bufferStart; p < this->bufferEnd; ++p) {
    if(p == this->gapStart) {
      assert(*p =='\0');
      std::cout<<"\nContents of gap ==========\n";
      std::cout<<"_";
    }
    else if(p == this->gapEnd) {
      std::cout<<"\nGap Ended============\n";
      std::cout<<*p;
    }
    else if(*p == '\0' )
      std::cout<<"_";
    else
      std::cout<<*p;
  }
  std::cout<<"\nPrinting end\n";
}
