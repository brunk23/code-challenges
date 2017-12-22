#include <iostream>
#include <string>
#include "art.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::getline;

int main() {
  TList tr;
  Art art(3,&tr);
  int i;
  string input;

  art.fill(".#...####");

  while( getline(cin, input) ) {
    tr.add(input);
  }

  for( i = 0; i < 18; i++ ) {
    if( i == 5 ) {
      cout << "5: " << art.pixels() << endl;
    }
    art.transform();
  }
  cout << "18: " << art.pixels() << endl;

  return 0;
}
