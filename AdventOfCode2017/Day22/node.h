#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class Node {
 private:
  struct iNode {
    iNode *next;
    int x;
    int y;
    bool infectedp;
  };

  iNode *head;
  iNode *tail;
  iNode *last;
  int lastloc[2];
  int mins[2];
  int maxs[2];

 public:
  Node() {
    head = 0;
    tail = 0;
    last = 0;
    mins[0] = 0;
    mins[1] = 0;
    maxs[0] = 0;
    maxs[1] = 0;
  };

  ~Node() {
    while(head) {
      tail = head->next;
      delete head;
      head = tail;
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
    last->infectedp = false;
    last->next = 0;
    last->x = x;
    last->y = y;
    if( head == 0 ) {
      head = last;
      tail = last;
    } else {
      tail->next = last;
      tail = last;
    }
  };

  void add(std::string row, int rownumber) {
    unsigned int i;

    for( i = 0; i < row.length(); i++ ) {
      findNode(rownumber,i);
      if( row[i] == '#' ) {
	infect();
      }
    }
  };

  /*
   * Changes last. It's the first step
   * so clean() and infect() can avoid
   * the lookup costs.
   */
  bool infected(int loc[2]) {
    findNode(loc[0],loc[1]);
    return last->infectedp;
  };

  int maxX() {
    return maxs[0];
  };

  int maxY() {
    return maxs[1];
  };
  
  void clean() {
    last->infectedp = false;
  };

  void infect() {
    last->infectedp = true;
  };
  
};

#endif
