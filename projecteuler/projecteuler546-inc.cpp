#include <iostream>

using std::cout;
using std::endl;

unsigned long long fsubk(unsigned int, long long);

/*
 * implement https://projecteuler.net/problem=546
 *
 * Currently not working for 7,100 or 2,1000 -- does for 5,10
 *
 * I must not understand part of this function, as my sums are
 * increasingly too small
 */
unsigned long long fsubk(unsigned int k, long long n) {
  long long extra = ( n % k ) + 1;
  long long sets = n / k;     /* We are going to group things */
  long long sum = 0;

  for( long long i = 0; i < sets; ++i ) {
    sum += ( i + 1 ) * k;
  }

  sum += ( sets + 1 ) * extra;

  return sum;
}

int main(int argc, char *argv[]) {
  cout << fsubk(2,1000) << endl;
  return 0;
}
