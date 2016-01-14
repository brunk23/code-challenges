#include <iostream>

using namespace std;

int main()
{
  unsigned long long y;
  long x;
  for( x = 1000000000; x < 1414213562; ++x ) {
    y = x*x;
    if( y % 10 != 0 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 9 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 8 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 7 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 6 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 5 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 4 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 3 ) {
      continue;
    }
    y /= 100;
    if( y % 10 != 2 ) {
      continue;
    }
    y /= 100;
    if( y % 10 == 1 ) {
      cout << "Found number: " << x << endl;
    }
  }
  return 0;
}
