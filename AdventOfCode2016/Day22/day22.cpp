#include <iostream>
#include <string>

#define MAXX 38
#define MAXY 28

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct node {
  int x;
  int y;
  int used;
  int avail;
};

// numbers x0-x37, y0-y27
node grid[MAXX][MAXY];

void setnode(int r, int c, int u, int a) {
  grid[r][c].x = r;
  grid[r][c].y = c;
  grid[r][c].used = u;
  grid[r][c].avail = a;
}

void readin() {
  string input;
  int i, x, y, used, avail;

  while( cin >> input ) {
    if( input[0] != '/' ) {
      // throw away leading lines
      continue;
    }
    x = 0;
    y = 0;
    i = 16;
    while( input[i] != '-' ) {
      x *= 10;
      x += input[i] - '0';
      i++;
    }
    i++;
    while( i < input.length() ) {
      y *= 10;
      y += input[i]- '0';
      i++;
    }
  }
}
