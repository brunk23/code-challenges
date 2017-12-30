#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include "chip.h"

int main(int argc, char *argv[]) {
  WINDOW *win;
  std::ifstream fp;
  Chip a;
  int height, width, key, status = step;
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
  getmaxyx(stdscr, height, width);
  
  win = newwin(height, width, 0, 0);
  nodelay(stdscr, TRUE);
  noecho();
  wrefresh(win);

  addstr("This is a test.\n");
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
    default:
      waddch(win, key);
      wrefresh(win);
      break;
    }
  }
  endwin();
  return 0;
}
