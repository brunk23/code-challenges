#include <iostream>
#include <string>

using std::string;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

#define LINES 201

void walker(string[LINES]);
bool canDown(string[LINES], int, int);
bool canUp(string[LINES], int, int);
bool canRight(string[LINES], int, int);
bool canLeft(string[LINES], int, int);
int findStart(string);

enum dirs { down, up, right, left };

/*
 * I am not sure these are correct, right now.  Should test that
 * we don't try and cross.
 */
bool canDown(string map[LINES], int row, int col) {
  if( (row < LINES - 2) && (map[row+1][col] != ' ' )) {
      return true;
  }
  return false;
}

bool canUp(string map[LINES], int row, int col) {
  if( (row > 0) && (map[row-1][col] != ' ') ) {
    return true;
  }
  return false;
}

bool canRight(string map[LINES], int row, int col) {
  if( (col < map[row].length() - 2) && (map[row][col+1] != ' ') ) {
    return true;
  }
  return false;
}

bool canLeft(string map[LINES], int row, int col) {
  if( (col > 0) && (map[row][col-1] != ' ') ) {
    return true;
  }
  return false;
}

int findStart(string a) {
  int i;

  for( i = 0; i < a.length(); i++ ) {
    if( '|' == a[i] ) {
      return i;
    }
  }
  return -1;
}

void walker(string map[LINES]) {
  int row = 0, col = 0;
  int direction = down;
  bool deadend = false;

  col = findStart(map[row]);

  while( !deadend ) {
    if( map[row][col] >= 'A' && map[row][col] <= 'Z' ) {
      cout << map[row][col];
    }
    switch( direction ) {
    case down:
      if( canDown(map, row, col) ) {
	row++;
	continue;
      } else {
	if( map[row][col] == '+' ) {
	  if( canRight(map, row, col) ) {
	    col++;
	    direction = right;
	    continue;
	  }
	  if( canLeft(map, row, col) ) {
	    col--;
	    direction = left;
	    continue;
	  }
	  deadend = true;
	}
      }
      break;

    case up:
      if( canUp(map, row, col) ) {
	row--;
	continue;
      } else {
	if( map[row][col] == '+' ) {
	  if( canLeft(map, row, col) ) {
	    col--;
	    direction = left;
	    continue;
	  }
	  if( canRight(map, row, col) ) {
	    col++;
	    direction = right;
	    continue;
	  }
	  deadend = true;
	}
      }
      break;

    case right:
      if( canRight(map, row, col) ) {
	col++;
	continue;
      } else {
	if( map[row][col] == '+' ) {
	  if( canUp(map, row, col) ) {
	    row--;
	    direction = up;
	    continue;
	  }
	  if( canDown(map, row, col) ) {
	    row++;
	    direction = down;
	    continue;
	  }
	  deadend = true;
	}
      }
      break;

    case left:
      if( canLeft(map, row, col) ) {
	col--;
	continue;
      } else {
	if( map[row][col] == '+' ) {
	  if( canDown(map, row, col) ) {
	    row++;
	    direction = down;
	    continue;
	  }
	  if( canUp(map, row, col) ) {
	    row--;
	    direction = up;
	    continue;
	  }
	  deadend = true;
	}
      }
      break;

    default:
      cout << "How did you get here?" << endl;
    }

  }

  cout << endl;
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

  cout << "Read " << x << " lines." << endl;

  return 0;
}
