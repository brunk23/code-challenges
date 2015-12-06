// Day 6 part 1
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::size_t;

#define LIGHTS 1000

int main()
{
  char grid[LIGHTS][LIGHTS];
  int pos[4];
  int point = 0;
  bool ondig = false;
  int operation = 0;
  
  for (int x = 0; x < LIGHTS; x++) {
    for (int y = 0; y < LIGHTS; y++) {
      grid[x][y] = 0;
    }
  }
  
  string input;
  while (getline(cin, input) ) {
    cout << "input: " << input << endl;
    operation = 0;
    point = 0;
    ondig = false;
    for (int x = 0; x < 4; x++ ) {
      pos[x] = 0;
    }
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
      cout << "Invalid input.!" << endl;
      continue;
    }
    for (int x = 0; x < input.size(); x++) {
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
	point++;
	break;
      default:
	if ( ondig ) {
	  point++;
	  ondig = false;
	}
      }
    }
    for (int x = pos[0]; x <= pos[2]; x++) {
      for (int y = pos[1]; y <= pos[3]; y++) {
	switch (operation) {
	case 1:
	  grid[x][y]=1;
	  break;
	case 2:
	  grid[x][y]=0;
	  break;
	default:
	  if ( grid[x][y] == 1 ) {
	    grid[x][y] = 0;
	  } else {
	    grid[x][y] = 1;
	  }
	}
      }
    }
  }

  point = 0;
  for (int x = 0; x < LIGHTS; x++ ) {
    for (int y = 0; y < LIGHTS; y++ ) {
      if (grid[x][y] == 1) {
	point++;
      }
    }
  }
  cout << "There are " << point << " lights on!" << endl;
  
  return 0;
}
