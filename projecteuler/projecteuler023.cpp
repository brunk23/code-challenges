#include <iostream>

using namespace std;

/*
 * Will solve problem 23
 */

int d(int);
int abundant(int);
int sumof2(int, int [], int);

int main()
{
  int abundant_numbers[10000], known = 0,
    x = 0, temp = 0, y = 0;
  long upper_bound;

  for( x = 0; x < 10000; ++x) {
    abundant_numbers[x] = 0;
  }
  
  upper_bound = 0;    /* From the problem statement */

  for(x = 1; x <= 28123; ++x) {
    temp = abundant(x);
    if( temp ) {
      abundant_numbers[known] = temp;
      known++;
    }
    if( !sumof2(x, abundant_numbers, known) ) {
      upper_bound += x;
    }
  }

  cout << "The sum was " << upper_bound << endl;
  
  return 0;
}

int sumof2(int x, int abundant_numbers[10000], int known) {
  int a, b;
  for( a = 0; a < known; ++a ) {
    for( b = 0; b <= a; ++b ) {
      if( (abundant_numbers[a]+abundant_numbers[b]) == x ) {
	return 1;
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
  if( fact > n ) {
    return n;
  }
  return 0;
}

/*
 * Will return the sum of all factors of a number
 * d(24) = 1 + 2 + 3 + 4 + 6 + 8 + 12 == 36
 */
int d(int numb) {
  int sum = 1, x = 0;

  for( x = 2; (x*x) < numb; ++x) {
    if( numb%x == 0 ) {
      sum += x;
      sum += numb/x;
    }
  }
  if( numb/x == x ) {
    sum += x;
  }

  return sum;
}
