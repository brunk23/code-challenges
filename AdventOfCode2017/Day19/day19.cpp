#include <iostream>
#include <string>

using std::string;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

#define LINES 201

enum dirs { up = 1, down = 2, right = 4, left = 8 };

int findStart(string);
void walker(string[LINES]);
bool validDest(string[LINES], int, int);
bool validLR(string[LINES], int, int);
bool validUD(string[LINES], int, int);

int findStart(string s) {
  int i;
  for( i = 0; i < s.length(); i++ ) {
    if( s[i] == '|' ) {
      return i;
    }
  }
  return -1;
}

bool validUD(string map[LINES], int row, int col) {
  if( !validDest(map, row, col) ) {
    return false;
  }
  if( map[row][col] == '-' ) {
    return false;
  }
  return true;
}

bool validLR(string map[LINES], int row, int col) {
  if( !validDest(map, row, col) ) {
    return false;
  }
  if( map[row][col] == '|' ) {
    return false;
  }
  return true;
}

bool validDest(string map[LINES], int row, int col) {
  if( row < 0 || row >= LINES ) {
    return false;
  }
  if( col < 0 || col >= map[row].length() ) {
    return false;
  }
  if( map[row][col] == ' ' ) {
    return false;
  }
  return true;
}

void walker(string map[LINES]) {
  int row = 0, col = 0, steps = 0;
  int direction = down;
  bool deadend = false;

  col = findStart(map[row]);

  while( !deadend ) {
    steps++;
    if( map[row][col] >= 'A' && map[row][col] <= 'Z' ) {
      cout << map[row][col];
    }

    // CHANGE DIRECTION
    if( map[row][col] == '+' ) {
      if( direction == up || direction == down ) {
	if( validLR(map, row, col - 1) ) {
	  direction = left;
	  col--;
	  continue;
	} else {
	  if( validLR(map, row, col + 1) ) {
	    direction = right;
	    col++;
	    continue;
	  } else {
	    deadend = true;
	    continue;
	  }
	}
      } else {
	if( validUD(map, row - 1, col) ) {
	  direction = up;
	  row--;
	  continue;
	} else {
	  if( validUD(map, row + 1, col) ) {
	    direction = down;
	    row++;
	    continue;
	  } else {
	    deadend = true;
	    continue;
	  }
	}
      }
    }

    switch( direction ) {
    case down:
      if( validDest(map, row+1, col) ) {
	row++;
      } else {
	deadend = true;
      }
      break;
      
    case up:
      if( validDest(map, row-1, col) ) {
	row--;
      } else {
	deadend = true;
      }
      break;
      
    case right:
      if( validDest(map, row, col+1) ) {
	col++;
      } else {
	deadend = true;
      }
      break;

    case left:
      if( validDest(map, row, col-1) ) {
	col--;
      } else {
	deadend = true;
      }
      break;

    default:
      cout << "How did you get here?" << endl;
      break;
    }    
  }
  cout << endl << "We went " << steps << " steps." << endl;
}

int main() {
  string map[LINES];
  string input;
  int x = 0;

  while( getline(cin, input) ) {
    map[x] = input;
    x++;
  }

  walker(map);

  return 0;
}
