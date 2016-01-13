#include <iostream>

using namespace std;

int distinct_primes(int);

int main()
{
  int n, count = 0, first = 0;

  for( n = 2; n < 1000000; ++n ) {
    if( distinct_primes(n) == 4 ) {
      ++count;
      if( count == 4 ) {
	break;
      }
      if( !first ) {
	first = n;
      }
    } else {
      count = 0;
      first = 0;
    }
  }

  cout << first << endl;
  
  return 0;
}

int distinct_primes(int n)
{
  int x = 0, i = 0;

  if( n < 2 ) {
    return 0;
  }

  for( i = 2; i*i < n; ) {
    if( n % i == 0 ) {
      ++x;
      while( n % i == 0 ) {
	n /= i;
      }
    }
    if( i == 2 ) {
      i = 3;
    } else {
      i += 2;
    }
  }

  if( n > 1 ) {
    ++x;
  }
	
  return x;
}
