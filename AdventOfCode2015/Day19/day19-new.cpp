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
int reduce(string s, int steps, Rules m, int min) {
  Rules r(m);
  steps++;
  r.reset();

  /*
    off = 0; off < length; off++;
    n = r.location(str, off);
    if( n >= 0 ) {
    r.replace(str, n);
    if( str != "e" ) {
    reduce(str, steps);
    }
    off += n;
    }

  */

  return 0;
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
  reduce(start, 0, master, -1);

  cout << start << endl;

  return 0;
}

