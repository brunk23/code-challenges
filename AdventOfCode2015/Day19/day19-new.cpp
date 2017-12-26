#include <iostream>
#include <string>
#include "rules.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::getline;

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

