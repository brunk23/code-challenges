#include <iostream>

using namespace std;

#define SIZE 50

bool validRoom(int, int);
int bitcount(int);
void fillroom(int [SIZE][SIZE]);
void printfloor(int [SIZE][SIZE]);
void stepAway(int [SIZE][SIZE], int, int);
void travel(int [SIZE][SIZE], int, int, int);
int roomsReached(int [SIZE][SIZE]);

int roomsReached(int floor[SIZE][SIZE]) {
  int x, y, count;

  count = 0;
  for(x = 0; x < SIZE; x++) {
    for( y = 0; y < SIZE; y++) {
      if( (floor[x][y] > 0) && (floor[x][y] <= 51) ) {
	count++;
      }
    }
  }
  return count;
}


void travel(int floor[SIZE][SIZE], int x, int y, int count) {
  if( floor[x][y] == -1 ) {
    return;
  }
  if( count == 50 ) {
    cout << "[" << x << "," << y << "]" << endl;
    floor[x][y] = 1;
    return;
  }

  if( x > 0 ) {
    travel(floor, x-1, y, count+1);
  }
  if( x < (SIZE-1) ) {
    travel(floor, x+1, y, count+1);
  }
  if( y > 0 ) {
    travel(floor, x, y-1, count+1);
  }
  if( y < (SIZE-1) ) {
    travel(floor, x, y+1, count+1);
  }
}
  
void stepAway(int floor[SIZE][SIZE], int x, int y) {
  int a = floor[x][y];
  
  a++;				// The new distance after a step.
  if( x > 0 ) {
    if( floor[x-1][y] > -1 ) {
      if( (floor[x-1][y]==0) || (a < floor[x-1][y]) ) {
	floor[x-1][y] = a;
	stepAway(floor, x-1, y);
      }
    }
  }

  if( x < (SIZE-1) ) {
    if( floor[x+1][y] > -1 ) {
      if( (floor[x+1][y]==0) || (a < floor[x+1][y]) ) {
	floor[x+1][y] = a;
	stepAway(floor, x+1, y);
      }
    }
  }
  
  if( y > 0 ) {
    if( floor[x][y-1] > -1 ) {
      if( (floor[x][y-1]==0) || (a < floor[x][y-1]) ) {
	floor[x][y-1] = a;
	stepAway(floor, x, y-1);
      }
    }
  }

  if( x < (SIZE-1) ) {
    if( floor[x][y+1] > -1 ) {
      if( (floor[x][y+1]==0) || (a < floor[x][y+1]) ) {
	floor[x][y+1] = a;
	stepAway(floor, x, y+1);
      }
    }
  }
}

void fillroom(int floor[SIZE][SIZE]) {
  int x, y;
  for( x = 0; x < SIZE; x++ ) {
    for( y = 0; y < SIZE; y++ ) {
      if( validRoom(x,y) ) {
	floor[x][y] = 0;
      } else {
	floor[x][y] = -1;
      }
    }
  }
}

void printfloor(int floor[SIZE][SIZE]) {
  int x, y;
  for( x = 0; x < SIZE; x++ ) {
    for( y = 0; y < SIZE; y++ ) {
      if( floor[x][y] == 0 ) {
	cout << ".";
      } else {
	cout << "#";
      }
    }
    cout << endl;
  }
}


int bitcount(int number) {
  int count = 0;
  while(number > 0) {
    if( (number%2) ) {
      count++;
    }
    number /= 2;
  }
  return count;
}

bool validRoom(int x, int y) {
  int number;
  number = x*x + 3*x + 2*x*y + y + y*y;
  number += 1362;		// Given in problem
  if( bitcount(number)%2 ) {
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  int floor[SIZE][SIZE];

  fillroom(floor);
  printfloor(floor);
  floor[1][1] = 1;
  stepAway(floor, 1, 1);

  cout << "Total rooms we can reach = " << roomsReached(floor) << endl;
  
  return 0;
}
