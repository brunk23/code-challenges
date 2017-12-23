#include <iostream>
#include <string>
#include "chip.h"

int main() {
  std::string input;
  Chip a;
  
  while( std::getline(std::cin, input) ) {
    a.add(input);
  }

  while(a.status() == running) {
    a.step();
  }
  return 0;
}
