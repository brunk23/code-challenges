#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define ARRSIZE 10000

int trows(int);

int main() {
  int count = 0, rows, index, y;
  double numbers[ARRSIZE];

  for(count = 0; count < ARRSIZE; ++count) {
    numbers[count] = 0;
  }

  count = 0;
  
  while( true ) {
    cin >> numbers[count];
    if( cin.eof() ) {
      break;
    }
    if( count == ARRSIZE ) {
      break;
    }
    ++count;
  }

  if( !(rows = trows(count))) {
    cout << "Error in input, we didn't read a triangle.\n";
    return 1;
  }
  
  for(count = rows-1; count > 0; --count) {
    index = (count*(count-1))/2;
    for( y = 0; y < count; ++y) {
      if( numbers[index+count+y] < numbers[index+count+y+1] ) {
	numbers[index+y] += numbers[index+count+y];
      } else {
	numbers[index+y] += numbers[index+count+y+1];
      }
    }
  }
  
  cout << "The minimum sum found was " << numbers[0] << endl;
  
  return 0;
}

int trows(int x) {
  int n;

  /* The max rows will be under 140 */
  for(n = 1; n < 140; ++n ) {
    if( n*(n+1)/2 == x ) {
      return n;
    }
    if( n*(n+1)/2 > x) {
      return 0;
    }
  }
  return 0;
}
