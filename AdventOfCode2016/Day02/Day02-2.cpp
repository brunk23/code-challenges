#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  string code;
  int x = 1, y = 1, i;
  
  static char keypad[5][5] = {
    {-1, -1,  '1', -1, -1},
    {-1,  '2',  '3',  '4', -1},
    { '5',  '6',  '7',  '8',  '9'},
    {-1, 'A','B','C',-1},
    {-1, -1, 'D',-1, -1}};
  
  while( cin >> code ) {
    for( i = 0; i < code.length(); i++ ) {
      switch( code[i] ) {
      case 'U':
	if( y > 0 ) {
	  if( keypad[y-1][x] != -1 ) {
	    y--;
	  }
	}
	break;
      case 'D':
	if( y < 4 ) {
	  if( keypad[y+1][x] != -1 ) {
	    y++;
	  }
	}
	break;
      case 'L':
	if( x > 0 ) {
	  if( keypad[y][x-1] != -1 ) {
	    x--;
	  }
	}
	break;
      case 'R':
        if ( x < 4 ) {
	  if( keypad[y][x+1] != -1 ) {
	    x++;
	  }
	}
	break;
      default:
	break;
      }
    }
    cout << keypad[y][x];
  }

  cout << endl;
  return 0;
}
