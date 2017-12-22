#ifndef CARRIER_H
#define CARRIER_H

#include "node.h"

// Adding 1 turns right, sub 1 turns left
enum Directions { up, right, down, left };

class Carrier {
 private:
  int location[2];
  int dir;
  Node *n;
  int caused;
  int increase;
  
 public:
  Carrier(Node *x, int i, int j) {
    location[0] = i;
    location[1] = j;
    caused = 0;
    increase = 0;
    n = x;
    dir = up;
  };

  ~Carrier() {
  };

  int cause() {
    return caused;
  };
  
  void burst() {
    if( n->infected(location) ) {
      dir = (dir + 1) % 4;
      n->clean();
      increase--;
    } else {
      if( dir == up ) {
	dir = left;
      } else {
	dir--;
      }
      n->infect();
      caused++;
      increase++;
    }
    switch( dir ) {
    case up:
      location[0]--;
      break;
    case down:
      location[0]++;
      break;
    case right:
      location[1]++;
      break;
    default:
      location[1]--;
      break;
    }
  };
  
};

#endif
