#include <iostream>
#include <string>
#include <sstream>

#define SIZE 256
#define GRID 128

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::to_string;

void swap( int [SIZE], unsigned int, unsigned int);
void printrow(int [GRID][GRID], int);
void hash( int [SIZE], string );
void filldisk(int [GRID][GRID], int [SIZE], int);
int countused(int [GRID][GRID]);
void traceregion(int [GRID][GRID], int x, int y, int n);
int findregions(int [GRID][GRID]);

int findregions(int d[GRID][GRID]) {
  int x, y, r = 2;

  for( x = 0; x < GRID; x++ ) {
    for( y = 0; y < GRID; y++ ) {
      if( d[x][y] == 1 ) {
	traceregion( d, x, y, r );
	r++;
      }
    }
  }
  return r - 2;
}

void traceregion(int d[GRID][GRID], int x, int y, int n) {
  d[x][y] = n;

  // Does not check wrap up.
  if( x > 0 ) {
    if( d[x - 1][y] == 1 ) {
      traceregion( d, x-1, y, n);
    }
  }

  // Does not check wrap down
  if( x < GRID - 1 ) {
    if( d[x + 1][y] == 1 ) {
      traceregion( d, x+1, y, n);
    }
  }

  // Does not check wrap left
  if( y > 0 ) {
    if( d[x][y-1] == 1 ) {
      traceregion( d, x, y-1, n );
    }
  }

  // Does not check wrap right
  if( y < GRID - 1 ) {
    if( d[x][y+1] == 1 ) {
      traceregion( d, x, y+1, n );
    }
  }
}

void printrow(int d[GRID][GRID], int row) {
  int i;
  for( i = 0; i < GRID; i++ ) {
    if( d[row][i] == 0 ) {
      cout << ".";
    } else {
      cout << "#";
    }
  }
  cout << endl;
}

int countused(int d[GRID][GRID]) {
  int i, j, sum = 0;
  for( i = 0; i < GRID; i++ ) {
    for( j = 0; j < GRID; j++ ) {
      if( d[i][j] > 0 ) {
	sum++;
      }
    }
  }
  return sum;
}

void filldisk(int d[GRID][GRID], int k[SIZE], int row) {
  unsigned int i;
  unsigned int curr = 0;
  unsigned int digit = 0;

  for( i = 0; i < SIZE; i++ ) {
    curr ^= k[i];
    if( 15 == (i % 16) ) {
      d[row][digit * 8 + 7] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 6] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 5] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 4] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 3] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 2] = curr % 2;
      curr /= 2;
      d[row][digit * 8 + 1] = curr % 2;
      curr /= 2;
      d[row][digit * 8] = curr % 2;
      curr = 0;
      digit++;
    }
  }
}

void swap(int list[SIZE], unsigned int start, unsigned int length) {
  unsigned int i,j;
  int tmp;
  i = start;
  j = start + length - 1;
  while( j > i ) {
    tmp = list[ i % SIZE ];
    list[ i % SIZE ] = list[ j % SIZE];
    list[ j % SIZE ] = tmp;
    i++;
    j--;
  }
}

void hash(int list[SIZE], string input) {
  int loc = 0, step = 0, i, len, loop;

  // Reset the list
  for( i = 0; i < SIZE; i++ ) {
    list[i] = i;
  }

  for( loop = 0; loop < 64; loop++ ) {
    for( i = 0; i < input.length(); i++ ) {
      len = input[i];
      swap(list, loc, len);
      loc = loc + len + step;
      loc %= SIZE;
      step++;
    }
    swap( list, loc, 17 );
    loc = loc + 17 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 31 );
    loc = loc + 31 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 73 );
    loc = loc + 73 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 47 );
    loc = loc + 47 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 23 );
    loc = loc + 23 + step;
    loc %= SIZE;
    step++;
  }
}

int main() {
  int list[SIZE], disk[GRID][GRID];
  unsigned int i;
  string input = "oundnydw";  // Test account
  //  string input = "vbqugkhl";  // My normal account
  //  string input = "flqrgnkx";  // The test code

  for( i = 0; i < GRID; i++ ) {
    hash(list, input + "-" + to_string(i) );
    filldisk(disk, list, i);
  }

  cout << "Used " << countused(disk) << " blocks." << endl;
  i = findregions(disk);
  cout << "Found " << i << " regions." << endl;

  return 0;
}
