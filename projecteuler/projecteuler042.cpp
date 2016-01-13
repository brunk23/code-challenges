#include <iostream>
#include <string>

using namespace std;

bool triangle(int);


int main() {
  string input;
  unsigned int i = 0, count = 0, word = 0;
  bool onword = false;
  
  while( getline(cin, input) ) {
    for( i = 0; i < input.size(); ++i ) {
      if( input[i] == '"' ) {
	if( onword ) {
	  if( triangle(word) ) {
	    ++count;
	  }
	  word = 0;
	}
	onword = ~onword;
      }
      if( isalpha(input[i]) ) {
	word += input[i] - 'A' + 1;
      }
    }
  }

  cout << count << " were triangle words." << endl;

  return 0;
}
  
bool triangle(int numb) {
  int x;
  for( x = 1; x*x/2 < numb; ++x ) {
    if( 2 * numb == x * ( x + 1 ) ) {
      return true;
    }
  }
  return false;
}
