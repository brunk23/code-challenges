#include <iostream>
#include <string>
#include "chip.h"

using std::cin;
using std::getline;
using std::string;
using std::cout;
using std::endl;

int main() {
  Chip c1;
  string input;

  while( getline(cin, input) ) {
    c1.add(input);
  }

  Chip c2(c1);
  c1.pair(c2);

  while( (c1.status() != stopped) || (c2.status() != stopped) ) {
    c1.step();
    c2.step();
  }

  return 0;
}
