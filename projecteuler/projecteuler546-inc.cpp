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
  long long sum = k;

  for( long long i = 1; i < sets; ++i ) {
    sum += ( i * k) * (sets - i + 1);
  }

  sum += ( sets + 1 ) * extra;

  return sum;
}

int main(int argc, char *argv[]) {
  cout << fsubk(5,20) << endl;
  return 0;
}
