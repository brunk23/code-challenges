#include <iostream>
#include "art.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int main() {
  TList tr;
  Art start(3,&tr);
  int i;
  unsigned int j;

  start.fill(".#...####");
  cout << start << endl;

  cout << start.pixels() << endl;

  Art tmp(3,&tr);
  j = 3;

  for( i = 0; i < 20; i++ ) {
    Art tmp(j,&tr);
    j =  tmp.nextsize();
    cout << i+2 << ": " << j << "x" << j << "=" << j*j<< endl;
  }
  
  return 0;
}
