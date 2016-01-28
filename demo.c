    // demo.c
    #include <ncurses.h>
    #include <unistd.h>
    int main(int argc, char *argv[]) {
      int parent_x, parent_y;
      int score_size = 3;
      initscr();
      noecho();
      curs_set(FALSE);
      // get our maximum window dimensions
      getmaxyx(stdscr, parent_y, parent_x);
      // set up initial windows
      WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
      WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
      // draw to our windows
      mvwprintw(field, 0, 0, "Field");
      mvwprintw(score, 0, 0, "Score");
      // refresh each window
      wrefresh(field);
      wrefresh(score);
      sleep(5);
      // clean up
      delwin(field);
      delwin(score);
      endwin();
      return 0;
    }
