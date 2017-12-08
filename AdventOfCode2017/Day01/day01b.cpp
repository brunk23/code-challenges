#include <iostream>
#include <string>

using namespace std;

int main() {
  string input;
  unsigned int a = 0, i, j, offset;

  while( cin >> input ) {
    offset = input.length() / 2;
    for( i = 0; i <= input.length(); i++ ) {
      j = (i + offset) % input.length();
      if(input[i] == input[j]) {
	a += input[i] - '0';
      }
    }
  }

  cout << a << endl;
}
