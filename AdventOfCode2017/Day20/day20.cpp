#include <iostream>
#include <string>
#include "particle.h"

using std::cin;
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

#define NUMBER 1000

int main() {
  Particle list[NUMBER];
  string input;
  int n = 0;

  /*
   * Read in the input file
   */
  while( getline(cin, input) ) {
    if( list[n].parseDef(input) != 0 ) {
      cerr << "Error parsing: " << input << endl;
      return 1;
    }
    n++;
  }
  

  return 0;
}
