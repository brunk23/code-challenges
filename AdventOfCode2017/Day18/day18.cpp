#include <iostream>
#include <string>
#include "chip.h"

using std::cin;
using std::getline;
using std::string;


int main() {
  Chip prog;
  string input;

  while( getline(cin, input) ) {
    prog.add(input);
  }

  prog.dump();

  return 0;
}
