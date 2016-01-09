#include <iostream>

/* This seems similar to the greatest path
 * down a triangle, except we need to move
 * right and down. */

using std::cout;
using std::endl;
using std::cin;

#define size 80

int main()
{
  long arr[size][size], x, y;

  for(x = 0; x < size; ++x) {
    for(y = 0; y < size; ++y) {
      cin >> arr[x][y];
    }
  }

  for( x = 1; x < size; ++x ) {
    arr[0][x] += arr[0][x-1];
  }
  for( x = 1; x < size; ++x ) {
    for( y = 0; y < size; ++y) {
      if( y ) {
	if( arr[x-1][y] < arr[x][y-1] ) {
	  arr[x][y] += arr[x-1][y];
	} else {
	  arr[x][y] += arr[x][y-1];
	}
      } else {
	arr[x][y] += arr[x-1][y];
      }
    }
  }

  cout << "The minimum path was: " << arr[size-1][size-1] << endl;

  return 0;
}
