#include <iostream>
#include "art.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main() {
  TList tr;
  Art start(4,&tr);

  start.fill("################");
  cout << start << endl;

  cout << start.pixels() << endl;
  
  return 0;
}
