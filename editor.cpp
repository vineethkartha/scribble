#include<iostream>
#include<fstream>
#include<vector>
#include"Document.cpp"
#include<ncurses.h>
#include<unistd.h>

int main()
{
  initscr();
  raw();
  noecho();
  char filename[10];
  char letter;
  int x,y;
  Document doc;
  WINDOW *edit=newwin(LINES-3,COLS,0,0);
  WINDOW *cli=newwin(3,COLS,LINES-3,0);
  keypad(edit, TRUE); 

  while(letter=getch())
    {
      if(letter==3)//Ctrl-C
	break;

      getyx(edit, y, x);

      if(letter>=32&&letter<=126)
	{
	  mvwaddch(edit,y,x,letter);
	  wrefresh(edit);
	}
      switch(letter)
	{
	  
	case 19: //Ctrl-s
	  echo();
	  wprintw(cli,"Enter Filename: ");
	  wscanw(cli,"%s",filename);
	  wprintw(cli,"%s",filename);
	  wrefresh(cli);
	  doc.save(filename);
	  noecho();
	  break;

	case 127:
	  if(x!=0)
	    x=x-1;
	  else
	    {
	      y=y-1;
	      x=COLS-1;
	    }
	  mvwaddch(edit,y,x,' ');
	  getyx(edit,y,x);
	  if(x==0&&y!=0)
	    {
	      x=COLS-1;
	      y=y-1;
	    }
	  else
	  x=x-1;
	  
	  wmove(edit,y,x);
	  wrefresh(edit);
	  doc.backspace();
	  break;
	case '\n':y=y+1;
	  x=0;
	  wmove(edit,y,x);
	  wrefresh(edit);
	  doc.insert(letter);
	  break;
	default:doc.insert(letter);
	  break;
	}
    }
  delwin(edit);
  delwin(cli);
  endwin();
  return 0;
}
