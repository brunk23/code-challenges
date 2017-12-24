#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

// Adding 1 turns right, sub 1 turns left
enum Directions { up, right, down, left };

const char clean = '.';
const char weakened = 'w';
const char infected = '#';
const char flagged = '~';

class Node {
 private:

  typedef char iNode;

 iNode *map;
  unsigned int maxs[2];
  int xmax;
  int ymax;
  int xoff;
  int yoff;

 public:
  Node() {
    int i, j;
    xmax = 26;
    ymax = 26;
    map = new iNode[ xmax * ymax ];
    for( i = 0; i < xmax; i++ ) {
      for( j = 0; j < ymax; j++ ) {
	map[i * ymax + j] = clean;
      }
    }
    maxs[0] = 0;
    maxs[1] = 0;
    xoff = 0;
    yoff = 0;
  };

  ~Node() {
    delete map;
    std::cerr << "End Dimensions: " << xmax << "x"
	      << ymax << std::endl;
  };

  unsigned int maxX() {
    return maxs[0];
  }

  unsigned int maxY() {
    return maxs[1];
  }
  
  void add(std::string row, unsigned int rownumber) {
    unsigned int i;

    if( rownumber > maxs[0] ) {
      maxs[0] = rownumber;
    }
    if( row.length() > maxs[1] ) {
      maxs[1] = row.length();
    }

    if( maxs[0] >= xmax ) {
      resize(down);
    }

    if( maxs[1] >= ymax ) {
      resize(right);
    }

    for( i = 0; i < row.length(); i++ ) {
      if( row[i] == '#' ) {
	map[(rownumber + xoff) * ymax + i + yoff] = infected;
      }
    }
  };

  void resize(int dir) {
    int nxmax = xmax, nymax = ymax, i, j, k = 0, m = 0;
    iNode *foo;
    int inc = 10;

    if( dir == down || dir == up ) {
      nxmax += inc;
    } else {
      nymax += inc;
    }
    if( dir == up ) {
      xoff += inc;
    }
    if( dir == left ) {
      yoff += inc;
    }
    iNode *tmp = new iNode[nxmax * nymax];
    for( i = 0; i < nxmax; i++ ) {
      for( j = 0; j < nymax; j++ ) {
	tmp[i * nymax + j] = clean;
      }
    }
    if( dir == up ) {
      k = inc;
    }
    if( dir == left ) {
      m = inc;
    }
    for( i = 0; i < xmax; i++ ) {
      for( j = 0; j < ymax; j++ ) {
	tmp[(i+k)*nymax + (j+m)] = map[i*ymax + j];
      }
    }
    foo = map;
    map = tmp;
    delete foo;
    xmax = nxmax;
    ymax = nymax;
  };

  void printmap(char m[], int x, int y) {
    int i, j;
    for( i = 0; i < x; i++ ) {
      for( j = 0; j < y; j++ ) {
	std::cout << m[i*y + j];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  };

  void checkloc(int loc[2]) {
    if( loc[0] + xoff >= xmax ) {
      resize(down);
    }
    if( loc[0] + xoff < 0 ) {
      resize(up);
    }
    if( loc[1] + yoff >= ymax ) {
      resize(right);
    }
    if( loc[1] + yoff < 0 ) {
      resize(left);
    }
  };

  char status(int loc[2]) {
    checkloc(loc);
    return map[(loc[0] + xoff) * ymax + loc[1] + yoff];
  };
  
  void chgstate(int loc[2]) {
    int calc;
    checkloc(loc);
    calc = (loc[0] + xoff) * ymax + loc[1] + yoff;
    switch( map[calc] ) {
    case clean:
      map[calc] = weakened;
      break;
    case weakened:
      map[calc] = infected;
      break;
    case infected:
      map[calc] = flagged;
      break;
    case flagged:
      map[calc] = clean;
      break;
    default:
      break;
    }
  };

};

#endif
