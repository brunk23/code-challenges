// Day 6 part 2
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

#define LIGHTS 1000

int main()
{
  // We have a grid of 1000 x 1000 lights (problem statement)
  char grid[LIGHTS][LIGHTS];
  int pos[4];			// x1,y1 and x2,y2
  int point = 0;		// which of the above we are finding
  bool ondig = false;		// are we on a number or not?

  // this reeks of "magic numbers" 1 = on, 2 = off, 3 = toggle
  // and is a dirty method. an enum would be better in most code
  int operation = 0;
  
  for (int x = 0; x < LIGHTS; x++) {
    for (int y = 0; y < LIGHTS; y++) {
      grid[x][y] = 0;
    }
  }
  
  string input;
  while (getline(cin, input) ) {

    // Reset the variables we are using to decode the input
    operation = 0;
    point = 0;
    ondig = false;
    for (int x = 0; x < 4; x++ ) {
      pos[x] = 0;
    }

    // Determine what we're going to be doing with these
    // two points. These are specific to the problem statement
    // and are fixed in the input file (we trust that the case
    // and format won't be mangled.
    if ( input.find("turn on") != string::npos ) {
      operation = 1;
    }
    if ( input.find("turn off") != string::npos ) {
      operation = 2;
    }
    if ( input.find("toggle") != string::npos ) {
      operation = 3;
    }
    if ( operation == 0 ) {
      // This shouldn't happen with the given input file
      // if it does, we ignore this line and go to the next
      cout << "Invalid input!" << endl;
      continue;
    }

    // Process the string looking for the 4 numbers that
    // are the points of the two corners of each rectangle
    for (unsigned int x = 0; x < input.size(); x++) {

      // First we handle digits we make a note that we were
      // on a digit already so we know if we need to go to the
      // next value in the array.
      switch ( input[x] ) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
	ondig = true;
	pos[point] *= 10;
	pos[point] += input[x] - '0';
	break;
      case ',':
	point++;		// A , separates two values
	break;
      default:
	if ( ondig ) {		// If we left digits, the next
	  point++;		// digit will be a new value
	  ondig = false;
	}
      }
    }

    // We now have the two points let's actually turn the
    // lights up or down as directed.
    for (int x = pos[0]; x <= pos[2]; x++) {
      for (int y = pos[1]; y <= pos[3]; y++) {
	switch (operation) {
	case 1:
	  // case 1 (turn on) increase by 1
	  grid[x][y]++;
	  break;
	case 2:
	  // case 2 (turn off) decrease by 1, unless 0
	  if ( grid[x][y] )
	    grid[x][y]--;
	  break;
	default:
	  // case 3 (toggle) increase by 2
	  grid[x][y]+=2;
	}
      }
    }
  }

  // We use point here to save the total brightness
  point = 0;

  // get the sum of all the values in the array.
  for (int x = 0; x < LIGHTS; x++ ) {
    for (int y = 0; y < LIGHTS; y++ ) {
      point += grid[x][y];
    }
  }

  // Tell the user what it was.
  cout << "The total brightness is " << point << " !" << endl;
  
  return 0;
}
