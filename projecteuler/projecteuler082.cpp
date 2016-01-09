#include <iostream>

/* This seems similar to the greatest path
 * down a triangle, except we need to move
 * right and down. */

using std::cout;
using std::endl;
using std::cin;

/*
 * For each spot in the current column, we
 * add the lowest of left, up+left, down+left
 * then move to the right
 */

#define size 80

int main()
{
  long arr[size][size], row, col, temp;
  long atemp[size], psum, trow;
  
  for(row = 0; row < size; ++row) {
    for(col = 0; col < size; ++col) {
      cin >> arr[row][col];
    }
  }

  for( col = 1; col < size; ++col ) {
    for( row = 0; row < size; ++row ) {
      temp = arr[row][col-1];
      psum = 0;
      for( trow = row-1; trow >= 0; trow--) {
	psum += arr[trow][col];
	if( (psum + arr[trow][col-1]) < temp ) {
	  temp = psum + arr[trow][col-1];
	}
      }
      psum = 0;
      for( trow = row+1; trow < size; trow++) {
	psum += arr[trow][col];
	if( (psum + arr[trow][col-1]) < temp ) {
	  temp = psum + arr[trow][col-1];
	}
      }
      atemp[row] = temp + arr[row][col];
    }
    for( row = 0; row < size; ++row ) {
      arr[row][col] = atemp[row];
    }
  }

  temp = arr[0][size-1];
  for( row = 1; row < size; ++row) {
    if( temp > arr[row][size-1] ) {
      temp = arr[row][size-1];
    }
  }
  
  cout << "The minimum path was: " << temp << endl;

  return 0;
}
