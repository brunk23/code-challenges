#include <iostream>

using std::cout;
using std::endl;

int d(int);

int main()
{
  int x = 0, sum = 0, a = 0;

  for( x = 2; x <= 10000; ++x ) {
    a = d(x);
    if( x!= a && x == d(a) ) {
      sum += x;
    }
  }

  cout << "Total found: " << sum << endl;
  
  return 0;
}


/*
 * Will return the sum of all factors of a number
 * d(24) = 1 + 2 + 3 + 4 + 6 + 8 + 12 == 36
 */
int d(int numb) {
  int sum = 0, x = 0;

  for( x = 1; x < numb; ++x) {
    if( numb%x == 0 ) {
      sum += x;
    }
  }

  return sum;
}
  
