#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

int main()
{
  int count = 0;
  stringstream number;
  string input = "1321131112";
  string next = "";
  char current = '\0';
  
  for (int i = 0; i < 40; ++i ) {
    next = "";    
    count = 0;
    for ( unsigned int x = 0; x < input.size(); x++) {

	if( current == input[x] ) {
		count++;
	} else {
		if( current ) {
			number.str("");
			number << count;
			next = next + number.str();
			number.str("");
			number << current;
			next = next + number.str();
		}
		current = input[x];
		count = 1;
	}
    }
    number.str("");
    number << count;
    next = next + number.str();
    number.str("");
    number << current;
    next = next + number.str();
    input = next;	
    cout << i << ": " << input.size() << endl;
  }
  
    cout << next << endl;
    cout << next.size() << endl;


  return 0;
}
