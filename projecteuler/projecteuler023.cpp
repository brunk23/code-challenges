#include <iostream>

using namespace std;

/*
 * Will solve problem 23
 */

int d(int);
int abundant(int);
int sumof2(int [], int, int []);

int main()
{
  int abundant_numbers[10000], all_numbers[28124];
  int known = 0, x = 0, temp = 0;

  for( x = 0; x < 10000; ++x) {
    abundant_numbers[x] = 0;
  }

  for( x = 0; x < 28124; ++x ) {
    all_numbers[x] = x;
  }

  /* Go through and find all the abundant numbers */
  for(x = 1; x <= 28123; ++x) {
    temp = abundant(x);
    if( temp ) {
      abundant_numbers[known] = temp;
      known++;
    }
  }

  /* Zero out all the numbers that are sums of 2
   * abundant numbers */
  sumof2(abundant_numbers, known, all_numbers);

  /* Sum all the numbers */
  known = 0;
  for( x = 0; x < 28124; ++x ) {
    known += all_numbers[x];
  }

  cout << "The sum was " << known << endl;
  
  return 0;
}

/*
 * Zero out the ones that sum, this was the key bottleneck
 * By only running this once, at the end, we save a ton of
 * time on this program.
 */
int sumof2(int abundant_numbers[10000], int known,
	   int all_numbers[28124]) {
  int a, b, c;
  for( a = 0; a < known; ++a ) {
    for( b = 0; b <= a; ++b ) {
      c = abundant_numbers[a] + abundant_numbers[b];
      if( c < 28124 ) {
	all_numbers[c] = 0;
      }
    }
  }
  return 0;
}

/*
 * Returns the number if it is abundant
 * Returns 0, if it isn't.
 */
int abundant(int n) {
  int fact;
  fact = d(n);
  if( fact > n+n ) {
    return n;
  }
  return 0;
}

/*
 * Rewriting this function to count primes and use
 * that for the sum of the factors did not improve
 * performance at all.
 * Will return the sum of all factors of a number
 * d(24) = 1 + 2 + 3 + 4 + 6 + 8 + 12 + 24 == 60
 */
int d(int n) {
  int p = 1, k = 0, prod = 1;

  for( k = 2; (k*k) <= n; ++k) {
    p = 1;
    while( n%k == 0 ) {
      p = p * k + 1;
      n /= k;
    }
    prod *= p;
  }
  if( n > 1 ) {
    prod *= 1+n;
  }

  return prod;
}
