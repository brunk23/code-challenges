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
    count += 2;
    for ( unsigned int x = 0; x < input.size(); x++) {
      count++;
      switch (input[x]) {
      case '\\':
	count++;
	break;
      case '"':
	count++;
	break;
      }
    }
  }
  
  cout << "The difference is: " << count - total << " characters." << endl;


  return 0;
}
