#include <iostream>
#include <string>
#include "md5.h"

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct path {
  struct path *next;
  string hist;
  int x;
  int y;
};

void printpath(path *);
path *step(int, int, string);
int canMove(path *);

/* create a new step to check */
path *step(int x, int y, string h) {
  path *head = new path;
  // head = (struct path *)malloc(sizeof(struct path));
  head->x = x;
  head->y = y;
  head->hist = h;
  head->next = 0;
  return head;
}

int canMove(path *loc) {
  int dir = 0;
  string m = md5( loc->hist );

  if( (loc->x > 0) && (m[0] >= 'b') && (m[0] <= 'f') ) {
    dir += UP;
  }
  if( (loc->x < 3) && (m[1] >= 'b') && (m[1] <= 'f') ) {
    dir += DOWN;
  }
  if( (loc->y > 0) && (m[2] >= 'b') && (m[2] <= 'f') ) {
    dir += LEFT;
  }
  if( (loc->y < 3) && (m[3] >= 'b') && (m[3] <= 'f') ) {
    dir += RIGHT;
  }
  return dir;
}

void printpath(path *curr) {
  cout << "[" << curr->x << "," << curr->y << "] " << curr->hist << endl;
}

int main() {
  path *head, *tail, *curr;
  bool found = false;
  int direc = 0;
  int longest = 0, t;
  string foo = "hhhxzeay";
  
  head = step(0,0,foo);
  tail = head;
  curr = head;
  
  while( head ) {
    if( (head->x == 3) && (head->y == 3) ) {
      t = head->hist.length() - 8;
      if( t > longest ) {
	cout << "New longest == " << t << endl;
	longest = t;
      }
      printpath(head);
      curr = head->next;
      delete head;
      head = curr;
      continue;
    }
    direc = canMove(head);
    if( direc & UP ) {
      foo = head->hist + "U";
      tail->next = step( head->x-1, head->y, foo );
      tail = tail->next;
    }
    if( direc & DOWN ) {
      foo = head->hist + "D";
      tail->next = step( head->x+1, head->y, foo );
      tail = tail->next;
    }
    if( direc & RIGHT ) {
      foo = head->hist + "R";
      tail->next = step( head->x, head->y+1, foo );
      tail = tail->next;
    }
    if( direc & LEFT ) {
      foo = head->hist + "L";
      tail->next = step( head->x, head->y-1, foo );
      tail = tail->next;
    }
    curr = head->next;
    delete head;
    head = curr;
  }

  return 0;
}
