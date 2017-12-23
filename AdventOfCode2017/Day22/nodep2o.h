#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

enum States { clean, weakened, infected, flagged };

class Node {
 private:
  struct iNode {
    int x;
    int y;
    int state;
  };

  iNode map[428][323];
  unsigned int maxs[2];
  int xoff;
  int yoff;

 public:
  Node() {
    int i, j;
    for( i = 0; i < 428; i++ ) {
      for( j = 0; j < 323; j++ ) {
	map[i][j].x = i;
	map[i][j].y = j;
	map[i][j].state = clean;
      }
    }
    maxs[0] = 0;
    maxs[1] = 0;
    xoff = 184;
    yoff = 146;
  };

  ~Node() {
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
    
    for( i = 0; i < row.length(); i++ ) {
      if( row[i] == '#' ) {
	map[rownumber+xoff][i+yoff].state = infected;
      }
    }
  };

  /*
   * Changes last. It's the first step
   * so clean() and infect() can avoid
   * the lookup costs.
   */
  int status(int loc[2]) {
    return map[loc[0]+xoff][loc[1]+yoff].state;
  };
  
  void chgstate(int loc[2]) {
    switch( map[loc[0]+xoff][loc[1]+yoff].state ) {
    case clean:
      map[loc[0]+xoff][loc[1]+yoff].state = weakened;
      break;
    case weakened:
      map[loc[0]+xoff][loc[1]+yoff].state = infected;
      break;
    case infected:
      map[loc[0]+xoff][loc[1]+yoff].state = flagged;
      break;
    case flagged:
      map[loc[0]+xoff][loc[1]+yoff].state = clean;
      break;
    default:
      break;
    }
  };
  
};

#endif
