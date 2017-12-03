#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(15) ;
  gp.addChar('V');
  gp.addChar('N');
  gp.addChar('E');
  gp.addChar('H');
  gp.Debugprint();

  gp.MoveGap(1);
  gp.addChar('i');
  gp.Debugprint();

  gp.MoveGap(14);
  gp.addChar('e');
  gp.addChar('t');

  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";

  return 0;
}
