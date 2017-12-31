#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include "chip.h"

void loop(Chip &a);

void uregwin(WINDOW *win, Chip &a) {
  int i;
  werase(win);
  for( i = 0; i < 26; i++ ) {
    wmove(win, 1 + i, 1);
    waddstr(win, a.regstr(i).c_str());
  }
  wmove(win, 3 + i, 1);
  waddstr(win, a.iptrstr().c_str());
  wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(win);
}

void loop(Chip &a) {
  WINDOW *mainwin, *regwin;
  int height, width, key, status = step;

  getmaxyx(stdscr, height, width);
  
  mainwin = newwin(height, width-15, 0, 0);
  regwin = newwin(height, 15, 0, width-15);
  nodelay(stdscr, TRUE);
  noecho();
  wrefresh(mainwin);
  wrefresh(regwin);

  while( a.status() == running ) {
    key = getch();
    if( status == running ) {
      a.step();
    }
    switch( key ) {
    case 'q':
      a.halt();
      break;
    case ERR:
      break;
    case 'r':
      status = running;
      break;
    case 's':
      status = step;
      a.step();
      break;
    case 'p':
      uregwin(regwin,a);
      break;
    default:
      waddch(mainwin, key);
      wrefresh(mainwin);
      wrefresh(regwin);
      break;
    }
  }

}

int main(int argc, char *argv[]) {
  std::ifstream fp;
  Chip a;
  std::string input;

  if( argc < 2 ) {
    std::cerr << "You need an input file." << std::endl;
    return 1;
  }

  fp.open(argv[1]);

  while( std::getline(fp, input) ) {
    a.add(input);
  }
  fp.close();

  initscr();

  loop(a);

  endwin();
  return 0;
}
