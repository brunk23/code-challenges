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
int validdirections(string[LINES],int, int, int);

enum dirs { down = 1, up = 2, right = 4, left = 8 };

int validdirections(string map[LINES], int row, int col, int dir) {
  int ndir = 0;
  
  if( canDown(map, row, col) ) {
    ndir += down;
  }
  if( canUp(map, row, col) ) {
    ndir += up;
  }
  if( canRight(map, row, col) ) {
    ndir += right;
  }
  if( canLeft(map, row, col) ) {
    ndir += left;
  }

  if( map[row][col] != '+' ) {
    if( dir == right || dir == left ) {
      ndir |= (right+left);
    } else {
      ndir |= (up + down);
    }
  }
  // Don't turn around.
  switch( dir ) {
  case up:
    ndir -= down;
    break;
  case down:
    ndir -= up;
    break;
  case right:
    ndir -= left;
    break;
  case left:
    ndir -= right;
    break;
  default:
    break;
  }

  return ndir;
}

/*
 * I am not sure these are correct, right now.  Should test that
 * we don't try and cross.
 */
bool canDown(string map[LINES], int row, int col) {
  if( (row < LINES - 2) && (map[row+1][col] != ' ' )) {
    if( map[row][col] == '+' && map[row+1][col] == '+' ) {
      return false;
    }
      return true;
  }
  return false;
}

bool canUp(string map[LINES], int row, int col) {
  if( (row > 0) && (map[row-1][col] != ' ') ) {
    if( map[row][col] == '+' && map[row-1][col] == '+' ) {
      return false;
    }
    return true;
  }
  return false;
}

bool canRight(string map[LINES], int row, int col) {
  if( (col < map[row].length() - 2) && (map[row][col+1] != ' ') ) {
    if( map[row][col] == '+' && map[row][col+1] == '+' ) {
      return false;
    }
    return true;
  }
  return false;
}

bool canLeft(string map[LINES], int row, int col) {
  if( (col > 0) && (map[row][col-1] != ' ') ) {
    if( map[row][col] == '+' && map[row][col-1] == '+' ) {
      return false;
    }
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
  int direction = down, possible;
  bool deadend = false;

  col = findStart(map[row]);

  while( !deadend ) {
    if( map[row][col] >= 'A' && map[row][col] <= 'Z' ) {
      cout << map[row][col];
    }
    possible = validdirections(map, row, col, direction);
    switch( direction ) {
    case down:
      if( possible & down ) {
	row++;
	continue;
      } else {
	if( possible & right ) {
	  col++;
	  direction = right;
	  continue;
	}
	if( possible & left ) {
	  col--;
	  direction = left;
	  continue;
	}
	deadend = true;
      }
      break;
      
    case up:
      if( possible & up ) {
	row--;
	continue;
      } else {
	if( possible & left ) {
	  col--;
	  direction = left;
	  continue;
	}
	if( possible & right ) {
	  col++;
	  direction = right;
	  continue;
	}
      }
      deadend = true;
      break;
      
    case right:
      if( possible & right ) {
	col++;
	continue;
      } else {
	if( possible & up ) {
	  row--;
	  direction = up;
	  continue;
	}
	if( possible & down ) {
	  row++;
	  direction = down;
	  continue;
	}
      }
      deadend = true;
      break;
    
    case left:
      if( possible & left ) {
	col--;
	continue;
      } else {
	if( possible & down ) {
	  row++;
	  direction = down;
	  continue;
	}
	if( possible & up ) {
	  row--;
	  direction = up;
	  continue;
	}
      }
      deadend = true;
      break;
    
    default:
      cout << "How did you get here?" << endl;
      break;
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
