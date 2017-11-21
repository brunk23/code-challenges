#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  string code;
  int x = 1, y = 1, i;
  
  static int keypad[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  
  while( cin >> code ) {
    for( i = 0; i < code.length(); i++ ) {
      switch( code[i] ) {
      case 'U':
	y -= 1;
	break;
      case 'D':
	y += 1;
	break;
      case 'L':
	x -= 1;
	break;
      case 'R':
	x += 1;
	break;
      default:
	break;
      }
      if( x < 0 ) x = 0;
      if( x > 2 ) x = 2;
      if( y < 0 ) y = 0;
      if( y > 2 ) y = 2;
    }
    cout << keypad[y][x];
  }

  cout << endl;
  return 0;
}
