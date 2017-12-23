#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

enum States { clean, weakened, infected, flagged };

class Node {
 private:
  struct iNode {
    iNode *next;
    int x;
    int y;
    int state;
  };

  iNode *head;
  iNode *last;
  int lastloc[2];
  int mins[2];
  int maxs[2];
  int total;

 public:
  Node() {
    head = 0;
    last = 0;
    total = 0;
    mins[0] = 0;
    mins[1] = 0;
    maxs[0] = 0;
    maxs[1] = 0;
  };

  ~Node() {
    std::cerr << std::endl << "Destroying Node List\n\n";
    std::cerr << "TLC: [" << mins[0] << "," << mins[1] << "]\n";
    std::cerr << "BRC: [" << maxs[0] << "," << maxs[1] << "]\n";
    std::cerr << "Structs created: " << total << " @ "
	     << sizeof(struct iNode) << " bytes each ("
	     << total * sizeof(struct iNode) << " bytes)"
	     << std::endl;
    while(head) {
      last = head->next;
      delete head;
      head = last;
    }
  };

  void findNode(int x, int y) {
    bool skip = false;
    if( x < mins[0] ) {
      mins[0] = x;
      skip = true;
    }
    if( x > maxs[0] ) {
      maxs[0] = x;
      skip = true;
    }
    if( y < mins[1] ) {
      mins[1] = y;
      skip = true;
    }
    if( y > maxs[1] ) {
      maxs[1] = y;
      skip = true;
    }

    if( !skip ) {
      // We need to search for it.
      last = head;
      while( last ) {
	if( last->x == x && last->y == y ) {
	  return;
	}
	last = last->next;
      }
    }
    // It did not exist. Make one.
    last = new iNode;
    last->state = clean;
    last->next = head;
    last->x = x;
    last->y = y;
    head = last;
    total++;
  };

  void add(std::string row, int rownumber) {
    unsigned int i;

    for( i = 0; i < row.length(); i++ ) {
      findNode(rownumber,i);
      if( row[i] == '#' ) {
	last->state = infected;
      }
    }
  };

  /*
   * Changes last. It's the first step
   * so clean() and infect() can avoid
   * the lookup costs.
   */
  int status(int loc[2]) {
    findNode(loc[0],loc[1]);
    /*
    std::cerr << loc[0] << "," << loc[1] << ": ";
    switch( last->state ) {
    case clean:
      std::cerr << "clean" << std::endl;
      break;
    case weakened:
      std::cerr << "weakened" << std::endl;
      break;
    case infected:
      std::cerr << "infected" << std::endl;
      break;
    case flagged:
      std::cerr << "flagged" << std::endl;
      break;
    default:
      break;
      }*/
    
    return last->state;
  };

  int maxX() {
    return maxs[0];
  };

  int maxY() {
    return maxs[1];
  };
  
  void chgstate() {
    switch( last->state ) {
    case clean:
      last->state = weakened;
      break;
    case weakened:
      last->state = infected;
      break;
    case infected:
      last->state = flagged;
      break;
    case flagged:
      last->state = clean;
      break;
    default:
      break;
    }
  };
  
};

#endif
