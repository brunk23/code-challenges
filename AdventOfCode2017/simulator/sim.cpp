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
    mvwprintw(win, 1 + i, 1, "%c: %08i", i+'a', a.regVal(i));
  }
  mvwprintw(win, 3 + i, 1, "instPtr: %i", a.iptr());
  wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(win);
}

void loop(Chip &a) {
  WINDOW *mainwin, *regwin;
  int height, width, key, status = step;

  getmaxyx(stdscr, height, width);
  nodelay(stdscr, TRUE);
  mainwin = newwin(height, width-15, 0, 0);
  regwin = newwin(height, 15, 0, width-15);
  noecho();
  key=getch();
  wmove(mainwin, 1, 1);
  waddstr(mainwin,"r=run, p=print, s=step, q=quit");
  wborder(mainwin, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(mainwin);

  uregwin(regwin,a);
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
      uregwin(regwin, a);
      break;
    case 'p':
      uregwin(regwin, a);
      break;
    default:
      waddch(mainwin, key);
      wrefresh(mainwin);
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
