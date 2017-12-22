#include <iostream>
#include <string>
#include "node.h"
#include "carrier.h"

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

int main() {
  Node holder;
  string input;
  int x = 0;
  
  while( getline(cin, input) ) {
    holder.add(input,x);
    x++;
  }

  Carrier carry(&holder, holder.maxX()/2, holder.maxY()/2);

  for( x = 0; x < 10000; x++ ) {
    carry.burst();
  }
  cout << "Caused: " << carry.cause() << endl;
  return 0;
}
