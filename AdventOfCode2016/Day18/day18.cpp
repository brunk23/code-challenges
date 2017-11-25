#include <iostream>
#include <string>

using namespace std;

string floor[40];

bool isTrap(int, int);

bool isTrap(int row, int col) {
  bool state = false;
  bool l, c, r;

  if( (col == 0) || (floor[row-1][col-1] == '.' ) ) {
    l = false;
  } else {
    l = true;
  }

  if( (col == floor[0].length() -1) || (floor[row-1][col+1] == '.') ) {
    r = false;
  } else {
    r = true;
  }

  if( floor[row-1][col] == '.' ) {
    c = false;
  } else {
    c = true;
  }

  if( (l && c) && !r ) {
    return true;
  }

  if( (c && r) && !l ) {
    return true;
  }

  if( !(c || r) && l ) {
    return true;
  }

  if( !(l || c) && r ) {
    return true;
  }
  return false;
}

int main() {
  int i, c, count = 0;

  for(i = 0; i < 40; i++ ) {
    floor[i] = "";
  }
  cin >> floor[0];

  for( i = 1; i <40; i++ ) {
    for(c = 0; c < floor[0].length(); c++ ) {
      if( isTrap(i,c) ) {
	floor[i] += '^';
      } else {
	floor[i] += '.';
      }
    }
  }

  for(i = 0; i < 40; i++ ) {
    for( c = 0; c < floor[0].length(); c++) {
      if( floor[i][c] == '.' ) {
	count++;
      }
    }
    cout << floor[i] << endl;
  }
  cout << count << endl;
  return 0;
}
