#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(6) ;
  gp.addChar('a');
  gp.addChar('b');
  gp.addChar('c');
  gp.addChar('d');
  gp.printBuffer();

  gp.MoveGap(2);
  gp.addChar('E');
  gp.printBuffer();
  gp.MoveGap(1);
  gp.addChar('F');
  gp.printBuffer();
  
  return 0;
}
