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

void printnode(int,int);

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
    i++;
    while( i < input.length() ) {
      y *= 10;
      y += input[i]- '0';
      i++;
    }
    i=0;
    used = 0;
    cin >> input;
    cin >> input;
    while( input[i] != 'T' ) {
      used *= 10;
      used += input[i] -'0';
      i++;
    }
    i=0;
    avail=0;
    cin >> input;
    while( input[i] != 'T' ) {
      avail *= 10;
      avail += input[i] -'0';
      i++;
    }
    setnode(x,y,used,avail);
  }
}

bool ispair( node a, node b ) {
  if( a.used == 0 ) {
    return false;
  }
  if( a.used < b.avail ) {
    return true;
  }
  return false;
}

void printnode(int x, int y) {
  cout << "x: " << grid[x][y].x << "\t";
  cout << "y: " << grid[x][y].y << "\t";
  cout << "USD: " << grid[x][y].used << "\t";
  cout << "AVL: " << grid[x][y].avail << "\n";
}

int main() {
  int NODES = MAXX*MAXY;
  int x, y, r, c, n, p,count = 0;
  readin();

  for(n = 0; n < NODES; n++ ) {
    x = n / MAXY;
    y = n % MAXY;
    for(p = n+1; p < NODES; p++ ) {
      r = p / MAXY;
      c = p % MAXY;
      if( ispair( grid[x][y], grid[r][c] ) ) {
	count++;
      }
      if( ispair( grid[r][c], grid[x][y] ) ) {
	count++;
      }
    }
  }

  cout << "There were " << count << " pairs." << endl;
}
