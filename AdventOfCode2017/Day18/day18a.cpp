#include <iostream>
#include <string>
#include "chipa.h"

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

  while( (c1.status() != stopped) ) {
    c1.step();
  }

  return 0;
}
