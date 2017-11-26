#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(20) ;
  gp.addChar('a');
  gp.addChar('b');
  auto a = gp.addChar('c');
  gp.addChar('d');
  gp.printBuffer();

  gp.MoveGap(a);
  gp.addChar('E');
  gp.printBuffer();
  return 0;
}
