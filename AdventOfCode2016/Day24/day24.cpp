#include <iostream>
#include <string>

#define ROWS 43
#define COLS 181

struct location {
  int row;
  int col;
  bool visited;
};

std::string map[ROWS];

using std::string;

void printLoc(string [ROWS]);
void duplicate(int [ROWS][COLS]);
void duppoints(location [8], location [8]);
void stepAway(int [ROWS][COLS], int, int);
int minDist(int [ROWS][COLS], location);

/**
 * LOCATIONS FROM INPUT
 *
 *  0: (7,171)  START
 *  1: (19,165)
 *  2: (39,131)
 *  3: (33,165)
 *  4: (7,17)
 *  5: (21,9)
 *  6: (41,5)
 *  7: (1,39)
 */
void initPoints(location points[8]) {
  points[0].visited = true;
  points[0].row = 7;
  points[0].col = 171;
  points[1].visited = false;
  points[1].row = 19;
  points[1].col = 165;
  points[2].visited = false;
  points[2].row = 39;
  points[2].col = 131;
  points[3].visited = false;
  points[3].row = 33;
  points[3].col = 165;
  points[4].visited = false;
  points[4].row = 7;
  points[4].col = 17;
  points[5].visited = false;
  points[5].row = 21;
  points[5].col = 9;
  points[6].visited = false;
  points[6].row = 41;
  points[6].col = 5;
  points[7].visited = false;
  points[7].row = 1;
  points[7].col = 39;
}

/* TEST
void initPoints(location points[8]) {
  points[0].visited = true;
  points[0].row = 1;
  points[0].col = 1;
  points[1].visited = false;
  points[1].row = 1;
  points[1].col = 3;
  points[2].visited = false;
  points[2].row = 1;
  points[2].col = 9;
  points[3].visited = false;
  points[3].row = 3;
  points[3].col = 1;
  points[4].visited = false;
  points[4].row = 3;
  points[4].col = 9;
  points[5].visited = true;
  points[5].row = 21;
  points[5].col = 9;
  points[6].visited = true;
  points[6].row = 41;
  points[6].col = 5;
  points[7].visited = true;
  points[7].row = 1;
  points[7].col = 39;
} */

int minDist(location points[8], location curr, int count) {
  int room[ROWS][COLS];
  int i, newcount = count, lcount = 0;
  location tmppoints[8], newloc;

  for( i = 0; i < 8; i++ ) {
    if( !(points[i].visited) ) {
      break;
    }
  }
  if( i == 8 ) {
    return count;
  }

  // Create a new map.
  duplicate(room);
  room[curr.row][curr.col] = 1;
  stepAway(room, curr.row, curr.col);

  for( i = 0; i < 8; i++ ) {
    if( !(points[i].visited) ) {
      duppoints(points, tmppoints);
      tmppoints[i].visited = true;
      newloc.row = tmppoints[i].row;
      newloc.col = tmppoints[i].col;
      newcount = minDist( tmppoints, newloc, count + room[ points[i].row ][ points[i].col ] - 1);
      if( lcount == 0 ) {
	lcount = newcount;
      }
      if( (newcount < lcount) ) {
	lcount = newcount;
      }
    }
  }
  return lcount;
}

void duppoints(location s[8], location d[8]) {
  int i;
  for( i = 0; i < 8; i++ ) {
    d[i].row = s[i].row;
    d[i].col = s[i].col;
    d[i].visited = s[i].visited;
  }
}

/*
 * Reuse from problem 13
 */
void stepAway(int floor[ROWS][COLS], int x, int y) {
  int a = floor[x][y];

  a++;                          // The new distance after a step.
  if( x > 0 ) {
    if( floor[x-1][y] > -1 ) {
      if( (floor[x-1][y]==0) || (a < floor[x-1][y]) ) {
        floor[x-1][y] = a;
        stepAway(floor, x-1, y);
      }
    }
  }

  if( x < (ROWS-1) ) {
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

  if( y < (COLS-1) ) {
    if( floor[x][y+1] > -1 ) {
      if( (floor[x][y+1]==0) || (a < floor[x][y+1]) ) {
        floor[x][y+1] = a;
        stepAway(floor, x, y+1);
      }
    }
  }
}

// Originally printed location. Changed to zero out floor plan
void printLoc() {
  int x, y;
  for(x = 0; x < ROWS; x++) {
    for( y=0; y < map[0].length(); y++ ) {
      if( map[x][y] >= '0' && map[x][y] <= '9' ) {
	std::cout << map[x][y] << ": (" << x << "," << y << ")\n";
      }
    }
  }
}

void duplicate(int copy[ROWS][COLS]) {
  int x,y;
  for(x = 0; x < ROWS; x++) {
    for(y = 0; y < COLS; y++) {
      if( map[x][y] == '#' ) {
	copy[x][y] = -1;
      } else {
	copy[x][y] = 0;
      }
    }
  }
}

int main() {
  string input;
  location points[8];
  location start;
  int count = 0;

  while( std::cin >> input ) {
    map[count] = input;
    count++;
 }
  printLoc();

  initPoints(points);
  start.row = points[0].row;
  start.col = points[0].col;

  count = minDist(points, start, 0);

  std::cout << count << std::endl;
  return 0;
}
