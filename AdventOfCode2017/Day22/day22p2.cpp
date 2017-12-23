#include <iostream>
#include <string>
#include "nodep2o.h"
#include "carrierp2o.h"

/*
 * I originally used nodep2.h and carrierp2.h to solve the
 * problem. But, the way I used dynamic memory and lists was
 * extremely expensive.  I was able to use them to give me
 * the limits for x and y, so I could create a static array.
 *
 * The dynamic memory program took 12 minutes and 54 seconds
 * to complete.  It was correct, but very slow.  Changing it
 * to use an array, sped it up to under 14 hundredths of a
 * second.  Over 5.5 thousand times faster!
 */

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

  for( x = 0; x < 10000000; x++ ) {
    carry.burst();
  }
  cout << "Caused " << carry.cause() << " infections" << endl;
  return 0;
}
