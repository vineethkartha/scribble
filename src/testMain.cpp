#include<iostream>
#include "DataStructures/gapbuffer/include/GapBuffer.hpp"
#include "GUI/vt100/include/guilib.hpp"
#include <string.h>

int main() {
  GapBuffer gp(2);
  VT100gui gui;
  int rows, cols;
  while (1) {
    char c = gui.editorReadKey();
    char *pc = &c;
    gui.getCursorPosition(&rows, &cols);
    //write(STDOUT_FILENO, &rows,1);
    //write(STDOUT_FILENO, cols,1);
    switch (c) {
      //Impelemnt the arrow keys
    
    case CTRL_KEY('q'):
      goto EXIT_POINT;
      break;
      case 'A':
	{
	  write(STDOUT_FILENO, "Hello", 5);
	  break;
	}
    case '\r':
      {
	char buf[15];
	//write(STDOUT_FILENO, "Hello", 5);
	gp.Insert('\n');
	gp.Insert('\r');
	rows++;
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,1);
	write(STDOUT_FILENO,buf,strlen(buf));
	break;
      }
    case 127:
      {
      //write(STDOUT_FILENO, "\x1b[H", 3);
      cols--;
      char buf[32];
      //snprintf(buf, sizeof(buf), "\x1b[%d;%dH",rows,cols);
      
      gp.Backspace();
      auto ptr = gp.printBuffer();
      write(STDOUT_FILENO, "\x1b[J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      //write(STDOUT_FILENO,buf,strlen(buf));
      write(STDOUT_FILENO, ptr.c_str(),ptr.size());
      
      break;
      }
    default:
      {
      //std::cout<<c<<"\n";
      printf("(%d) %c\n",c,c);
      gp.Insert(c);
      auto ptr = gp.printBuffer();
      write(STDOUT_FILENO, "\x1b[1J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      write(STDOUT_FILENO, ptr.c_str(),ptr.size());
      break;
      }
    }
  }
 EXIT_POINT:
  std::cout<<"\n\n";
  auto a = gp.printBuffer();
  std::cout<<a<<"\n\n";
  std::cout<<rows<<"\n"<<cols<<"\n";
  return 0;
}
