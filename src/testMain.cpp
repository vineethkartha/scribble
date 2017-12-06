#include<iostream>
#include "include/GapBuffer.hpp"

int main() {
  GapBuffer gp(2) ;
  gp.Insert('a');
  gp.Insert('b');
  gp.Insert('c');
  gp.Insert('d');
  gp.Insert('e');
  gp.Debugprint();

  gp.MoveGap(1);
  gp.Delete();
  //gp.Insert('i');
  gp.Debugprint();

  gp.MoveGap(14);
  gp.Insert('e');
  gp.Insert('t');
  
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";

  return 0;
}
