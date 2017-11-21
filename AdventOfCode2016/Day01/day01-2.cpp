#include <iostream>
#include <string>

int addAmount(int, int);
int absolute(int);
int fixdirection(int);
int addVisited();
void found();

struct location {
  int ns;
  int ew;
};

location visited[1000];

// Turning right adds one, turning left subtracts 1.
enum directions { NORTH, EAST, SOUTH, WEST };
int north_south = 0, east_west = 0;

using std::cin;
using std::cout;
using std::endl;
using std::string;

int absolute(int a) {
  if(a < 0) {
    return a * -1;
  }
  return a;
}

int addVisited() {
  int i;
  for(i = 0; i < 1000; i++) {
    if( (visited[i].ns == 0) && (visited[i].ew == 0) ) {
      visited[i].ns = north_south;
      visited[i].ew = east_west;
      break;
    }
    if( (visited[i].ns == north_south) &&
	(visited[i].ew == east_west) ) {
      found();
      return 1;
    }
  }
  return 0;
}

int fixdirection( int direction ) {
  if( direction > WEST ) {
    direction -= 4;
  }
  if( direction < NORTH ) {
    direction += 4;
  }
  return direction;
}

int addAmount(int direction, int amount) {
  int i;
  for( i = 0; i < amount; i++ ) {
    switch( direction ) {
    case NORTH:
      north_south += 1;
      break;
    case SOUTH:
      north_south -= 1;
      break;
    case EAST:
      east_west += 1;
      break;
    case WEST:
      east_west -= 1;
      break;
    default:
      break;
    }
    addVisited();
  }
  return 0;
}

void found() {
  static int x = 0;
  if( x == 0 ) {
    cout << "We have been here before" << endl;
    cout << "NS: " << north_south << endl;
    cout << "EW: " << east_west << endl;
    cout << "Total distance = " << abs(east_west)+abs(north_south) << endl;
    x = 1;
  }
}
  
int main(int argc, char *argv[]) {
  int i, direction=NORTH, amount;
  string input;

  while( cin >> input ) {
    amount = 0;
    for( i = 0; i < input.length(); i++) {
      if( 'R' == input[i] ) {
	direction++;
      }
      if( 'L' == input[i] ) {
	direction--;
      }
      if( ',' == input[i] ) {
	direction = fixdirection(direction);
	addAmount(direction, amount);
	amount = 0;
      }
      if( ('0' <= input[i]) && ('9' >= input[i]) ) {
	amount *= 10;
	amount += input[i] - '0';
      }
    }
    if( amount > 0 ) {
      direction = fixdirection(direction);
      addAmount(direction, amount);
    }
  }
  
  return 0;
}
