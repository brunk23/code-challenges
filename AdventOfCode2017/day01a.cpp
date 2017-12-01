#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  unsigned int a = 0, i;

  while( cin >> input ) {
    if( input.length() > 1 ) {
      if( input[0] == input[ input.length() - 1 ] ) {
	a += input[0] - '0';
      }
    }
    for( i = 0; i <= input.length() - 1; i++ ) {
      if(input[i] == input[i+1]) {
	a += input[i] - '0';
      }
    }
  }

  cout << a << endl;
}
