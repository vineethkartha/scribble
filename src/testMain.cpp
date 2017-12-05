#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(15) ;
  gp.Insert('V');
  gp.Insert('N');
  gp.Insert('E');
  gp.Insert('H');
  gp.Debugprint();

  gp.MoveGap(1);
  gp.Delete();
  gp.Insert('i');
  gp.Debugprint();

  /*gp.MoveGap(14);
  gp.Insert('e');
  gp.Insert('t');
  */
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";

  return 0;
}
