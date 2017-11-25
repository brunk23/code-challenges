#include <iostream>

enum kind {generator=10, microchip};
enum elements {thu=1, plu, str, pro, rut);

struct Item {
  int type;
  int isotope;
};

int currentFloor;
Item floor[4][10];

void moveUP( int, int);
void moveDown( int, int );
void init();

void moveUP( int a, int b ) {

}

void moveDown( int a, int b ) {

}

void init() {
  int f,i;

  currentFloor = 0;
  for(f = 0; f < 4; f++) {
    for( i = 0; i < 10; i++) {
      floor[f][i].type = 0;
      floor[f][i].isotope = 0;
    }
  }
}

int main() {

  init();
  
  return 0;
}
