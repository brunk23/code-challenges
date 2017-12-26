#include <iostream>
#include <string>
#include "rules.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::getline;

// The basic plan here will be to find all occurences
// of the current right side of the string, try reducing them
// and recursively work down the tree until we find a solution
int reduce() {

}

int main() {
  Rules master;
  string input;
  string start;
  unsigned int endleft;
  unsigned int i;
  
  while(getline(cin,input)) {
    endleft = 0;
    start = input;
    for(i = 0; i<input.length(); i++) {
      if( endleft == 0 && input[i] == ' ' ) {
	endleft = i;
      }
      if( endleft > 0 && input[i] >= 'A' && input[i] >= 'Z') {
	master.add(input.substr(0,endleft),input.substr(i-1));
	break;
      }
    }
  }

  cout << start << endl;
  
  return 0;
}

