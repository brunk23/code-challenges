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
  int ns1=100,ew1=100;
  int ns2=100,ew2=100;
  int input, count = 0;
  int santa = 0, change=1;

  for ( int x = 0; x < MAX; ++x ) {
    for ( int y = 0; y < MAX; ++y ) {
      house_array[x][y]=0;
    }
  }  
  
  while ( (input = cin.get()) != EOF ) {
    if( santa == 0 ) {
      if(house_array[ns1][ew1] == 0) {
	cout << "A new house!" << endl;
	count++;
      } else {
	cout << "An old house!" << endl;
      }
      house_array[ns1][ew1]+=1;
      santa = 1;
    } else { 
      if(house_array[ns2][ew2] == 0) {
	cout << "A new house!" << endl;
	count++;
      } else {
	cout << "An old house!" << endl;
      }
      house_array[ns2][ew2]+=1;
      santa = 0;
    }
  
    switch ( input ) {
    case '^':
      santa ? --ns1 : --ns2;
      if ( ns2 < 0 || ns1 < 0 ) {
	cout << "Error, too far north!" << endl;
	return 1;
      }
      break;
    case '>':
      santa ? ++ew1 : ++ ew2;
      if ( ew2 >= MAX || ew2 >=MAX ) {
	cout << "Error, too far east" << endl;
	return 1;
      }
      break;
    case '<':
      santa ? --ew1 : --ew2;
      if ( ew2 < 0 || ew1 < 0 ) {
	cout << "Error, too far west" << endl;
	return 1;
      }
      break;
    case 'v':
    case 'V':
      santa ? ++ns1 : ++ ns2;
      if ( ns2 >= MAX || ns2 >=MAX ) {
	cout << "Error too far south" << endl;
      }
      break;
    default:
      change =0;
      // we ignore all other input.
      break;
    }
  }
  
  cout << "The total number of houses was " << count << endl;
  
  return 0;
}
