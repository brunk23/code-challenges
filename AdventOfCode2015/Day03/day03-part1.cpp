/*
 * Advent of code Day 3 part 1
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int MAX = 2000;

int main() {
  char house_array[MAX][MAX];
  int ns=100,ew=100;
  int input, count = 0;

  for ( int x = 0; x < MAX; ++x ) {
    for ( int y = 0; y < MAX; ++y ) {
      house_array[x][y]=0;
    }
  }  
  
  while ( (input = cin.get()) != EOF ) {
    if(house_array[ns][ew] == 0) {
      cout << "A new house!" << endl;
      count++;
    } else {
      cout << "An old house!" << endl;
    }
    house_array[ns][ew]+=1;
    switch ( input ) {
    case '^':
      --ns;
      if ( ns < 0 ) {
	cout << "Error, too far north!" << endl;
	return 1;
      }
      break;
    case '>':
      ++ew;
      if ( ew >= MAX ) {
	cout << "Error, too far east" << endl;
	return 1;
      }
      break;
    case '<':
      --ew;
      if ( ew < 0 ) {
	cout << "Error, too far west" << endl;
	return 1;
      }
      break;
    case 'v':
    case 'V':
      ++ns;
      if ( ns >= MAX ) {
	cout << "Error too far south" << endl;
      }
      break;
    default:
      // we ignore all other input.
      break;
    }
  }
    
  cout << "The total number of houses was " << count << endl;
  
  return 0;
}
