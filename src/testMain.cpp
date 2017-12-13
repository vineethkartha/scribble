#include<iostream>
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include "GUI/vt100/include/guilib.hpp"

int main() {
  GapBuffer gp(2);
  VT100gui gui;

  while (1) {
    char c = gui.editorReadKey();
    char *pc = &c;
    switch (c) {
    case CTRL_KEY('q'):
      goto EXIT_POINT;
      break;
    default:
      gp.Insert(c);
      write(STDOUT_FILENO, pc,1);
      break;
    }
  }
 EXIT_POINT:
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";
  return 0;
}
