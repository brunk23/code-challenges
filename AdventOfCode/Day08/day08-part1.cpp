#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

int main()
{
  int count = 0;
  unsigned int total = 0;
  string input;
  
  while ( getline(cin, input) ) {
    total += input.size();
    for ( unsigned int x = 0; x < input.size(); x++) {
      count++;
      switch (input[x]) {
      case '\\':
	x++;
	if ( input[x] == 'x' ) {
	  x += 2;
	}
	break;
      case '"':
      case '\n':
      case '\r':
      case ' ':
      case '\t':
	count--;
	break;
      }
    }
  }
  
  cout << "The difference is: " << total - count << " characters." << endl;


  return 0;
}
