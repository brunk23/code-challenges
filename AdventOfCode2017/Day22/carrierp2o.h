#ifndef CARRIER_H
#define CARRIER_H

#include "nodep2.h"

// Adding 1 turns right, sub 1 turns left
enum Directions { up, right, down, left };

class Carrier {
 private:
  int location[2];
  int dir;
  Node *n;
  int caused;
  
 public:
  Carrier(Node *x, int i, int j) {
    location[0] = i;
    location[1] = j;
    caused = 0;
    n = x;
    dir = up;
  };

  ~Carrier() {
  };

  int cause() {
    return caused;
  };
  
  void burst() {
    switch( n->status(location) ) {
    case clean:
      dir = (dir + 3) % 4;
      break;
    case weakened:
      caused++;
      break;
    case infected:
      dir = (dir + 1) % 4;
      break;
    case flagged:
      dir = (dir + 2) % 4;
      break;
    default:
      break;
    }
    n->chgstate(location);
    
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
