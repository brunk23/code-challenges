#include <iostream>

using std::cout;
using std::endl;

enum kind {generator=1, microchip=2};
enum elements {thu=4, plu=8, str=16, pro=32, rut=64};

#define ITEMS 10

struct attempt {
  int moves;
  int currentFloor;
  int floor[4][ITEMS];
  attempt *next;
};

void moveUP( int, int);
void moveDown( int, int );
attempt *newAttempt(int, int, int [4][ITEMS]);
bool winner( attempt * );
bool floorOK( attempt * );

/*
 * winning state has nothing on floors
 * 1-3.
 */
bool winner(attempt *foo) {
  int j, i, sum=0;

  for(j = 0; j < 3; j++) {
    for(i = 0; i < ITEMS; i++) {
      sum += foo->floor[j][i];
    }
  }
  if( sum == 0 ) {
    return true;
  }
  return false;
}
  
bool floorOK(attempt *foo) {
  int i;
  int gensum = 0;
  int micsum = 0;

  for( i = 0; i < ITEMS; i++ ) {
    if( (foo->floor[foo->currentFloor][i]&1) == 1 ) {
      gensum += foo->floor[foo->currentFloor][i]-1;
    }
    if( (foo->floor[foo->currentFloor][i]&2) == 2 ) {
      micsum += foo->floor[foo->currentFloor][i]-2;
    }
  }
  if( gensum > 0 ) {
    if( (gensum & micsum) == micsum ) {
      return true;
    }
    return false;
  }
  return true;
}

void moveUP( int a, int b ) {

}

void moveDown( int a, int b ) {

}

attempt *newAttempt(int fl, int m, const int c[4][ITEMS]) {
  attempt *r = new attempt;
  int f,i;

  r->moves = m;
  r->currentFloor = fl;

  for(f = 0; f < 4; f++) {
    for(i = 0; i < ITEMS; i++) {
      r->floor[f][i] = c[f][i];
    }
  }
  r->next = 0;
}

const int startingState[4][ITEMS] = {
  {thu+generator, thu+microchip, plu+generator, str+generator,0,0,0,0,0,0},
  {plu+microchip, str+microchip, 0, 0, 0, 0, 0, 0, 0, 0},
  {pro+generator, pro+microchip, rut+generator, rut+microchip,0,0,0,0,0,0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int main() {
  attempt *head = newAttempt(0, 0, startingState);
  attempt *tail = head;
  attempt *curr = head;

  if( floorOK(head) ) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  
  return 0;
}
