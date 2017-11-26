#include <iostream>

enum kind {generator=0, microchip};
enum elements {thu=2, plu=4, str=8, pro=16, rut=32};

struct attempt {
  int moves;
  int currentFloor;
  int floor[4][10];
  attempt *next;
};

void moveUP( int, int);
void moveDown( int, int );
attempt *newAttempt(int, int, int [4][10]);

void moveUP( int a, int b ) {

}

void moveDown( int a, int b ) {

}

attempt *newAttempt(int fl, int m, const int c[4][10]) {
  attempt *r = new attempt;
  int f,i;

  r->moves = m;
  r->currentFloor = fl;

  for(f = 0; f < 4; f++) {
    for(i = 0; i < 10; i++) {
      r->floor[f][i] = c[f][i];
    }
  }
  r->next = 0;
}

const int startingState[4][10] = {
  {thu+generator, thu+microchip, plu+generator, str+generator,0,0,0,0,0,0},
  {plu+microchip, str+microchip, 0, 0, 0, 0, 0, 0, 0, 0},
  {pro+generator, pro+microchip, rut+generator, rut+microchip,0,0,0,0,0,0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int main() {
  attempt *head = newAttempt(0, 0, startingState);
  attempt *tail = head;
  attempt *curr = head;
  
  
  return 0;
}
