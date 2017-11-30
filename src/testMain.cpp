#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(10) ;
  gp.addChar('a');
  gp.addChar('b');
  gp.addChar('c');
  gp.addChar('d');
  gp.printBuffer();

  gp.MoveGapBack(2);
  gp.addChar('E');
  gp.printBuffer();
  gp.MoveGapBack(1);
  gp.addChar('F');
  gp.printBuffer();
  gp.MoveGapFor(4); // this should not cause an exception
  gp.addChar('G');
  gp.printBuffer();

  gp.MoveGapFor(9); 
  gp.addChar('H');
  gp.printBuffer();
  return 0;
}
