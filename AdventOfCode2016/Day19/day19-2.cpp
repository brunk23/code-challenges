#include <iostream>

/*
 * First solution was too slow.  Watched relevant
 * numberphile video on Josephus problem. Then
 * I did the first 30 by hand.  Used the pattern
 * that was obvious from the table.  
 */

using namespace std;

#define ELVES 3012210

int main() {
  int i, count = ELVES, s, w;

  i = 1;
  while( i < count ) {
    i *= 3;
  }
  i /= 3;

  s = 0;
  w = i;
  while( w <= 2*i ) {
    if( w == count ) {
      cout << "Winner here: " << s << endl;
      return 0;
    }
    w++;
    s++;
  }
  while( w < count ) {
    w++;
    s +=2;
  }
  cout << "Winner here; " << s << endl;
  
  return 0;
}
