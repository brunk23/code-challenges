#include <iostream>

using namespace std;

int sofe(int *,int);
int isprime(int *, int, int);

int main() {
  int p[90000];
  int a, b, n;
  int max = 0, max_a = 0, max_b = 0;
  
  sofe(p,90000);

  for( a = -1000; a <= 1000; ++a ) {
    for( b = -1000; b <= 1000; ++b ) {
      n = 0;
      while( isprime( p, 90000,
		      ( n*n + n*a + b ) ) ) {
	n++;
      }
      if( n > max ) {
	max = n;
	max_a = a;
	max_b = b;
      }
    }
  }
  
  cout << "Max found at a: " << max_a
       << " b: " << max_b << endl;
  cout << "The product is " << (max_b*max_a) << endl;

  return 0;
}

int isprime(int *a, int len, int n) {
  int x;
  if ( n < 2 ) {
    return 0;
  }
  if ( n > len ) {
    return 0;
  }
  for( x = 0; x <= n; ++x ) {
    if( a[x] == n ) {
      return 1;
    }
  }
  return 0;
}

/*
 * Quickly produce primes
 */
int sofe(int *a, int top) {
  int x, i = 2;
  
  for(x = 0; x < top; ++x) {
    a[x] = x;
  }
  a[1] = 0;

  while( 1 ) {
    if( a[i] ) {
      for(x = a[i]+a[i]; x < top; x += a[i]) {
	a[x] = 0;
      }
      i++;
    } else {
      i++;
    }
    if( i >= top ) {
      break;
    }
  }
  return 0;
}
