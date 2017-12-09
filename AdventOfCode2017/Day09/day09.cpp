#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::cerr;

/*
 * Ideally, we could make this program smart enough
 * to parse the input into states, which contain a
 * variable list of states and strings.  But, first
 * Let's get part A done.
 *
 * Part be is a simple extension of part A, just
 * one additional line of code, plus the output,
 * so there's no need to build the data structures.
 */

int main() {
  string s;
  int count = 0, depth = 0, garbageChars = 0;
  unsigned int i;
  bool inGarbage = false;
  
  if( !( getline(cin, s) ) ) {
    cerr << "INPUT FAILURE" << endl;
  }

  for( i = 0; i < s.length(); i++ ) {
    if( inGarbage ) {
      if( s[i] == '>' ) {
	inGarbage = false;
	continue;
      }
      if( s[i] == '!' ) {
	i++;
	continue;
      }
      garbageChars++;
      continue;
    }

    if( s[i] == '<' ) {
      inGarbage = true;
      continue;
    }
    if( s[i] == '{' ) {
      depth++;
      count += depth;
      continue;
    }
    if( s[i] == '}' ) {
      depth--;
    }
    // Everything else is ignore.
  }

  cout << "The total score is " << count << endl;
  cout << "There were " << garbageChars << " garbage characters" << endl;
  
  return 0;
}
