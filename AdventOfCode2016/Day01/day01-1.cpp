#include <iostream>
#include <string>

void addAmount(int, int);
int absolute(int);
int fixdirection(int);

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

int fixdirection( int direction ) {
  if( direction > WEST ) {
    direction -= 4;
  }
  if( direction < NORTH ) {
    direction += 4;
  }
  return direction;
}

void addAmount(int direction, int amount) {

  cout << "Adding: " << amount << " to " << direction << endl;

  switch( direction ) {
  case NORTH:
    north_south += amount;
    break;
  case SOUTH:
    north_south -= amount;
    break;
  case EAST:
    east_west += amount;
    break;
  case WEST:
    east_west -= amount;
    break;
  default:
    break;
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

  cout << "NS: " << north_south << endl;
  cout << "EW: " << east_west << endl;
  cout << "Total distance = " << abs(east_west)+abs(north_south) << endl;
  
  return 0;
}
