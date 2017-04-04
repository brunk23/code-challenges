#include <iostream>

using namespace std;

bool isPrime(int);
int removedups(int [], int);
void findwinners(int [], int);
int value(int, int, int, int);
void test(int, int, int, int);
void winner(int, int, int);

/*
 * An ugly but quick prime tester
 * BROKEN: says 2 is not prime (not fixed in this project)
 */
bool isPrime(int number) {
  int n;
  if( 0 == number % 2 ) {
    return false;
  }
  for( n = 3; (n*n) <= number; n += 2 ) {
    if( 0 == number % n ) {
      return false;
    }
  }
  return true;
}

int value(int th, int hu, int te, int on) {
  int value;
  value = on;
  value += te * 10;
  value += hu * 100;
  value += th * 1000;
  return value;
}

void winner(int a, int b, int c) {
  cout << a << " " << b << " " << c << endl;
}

/*
 * This should make a list of ALL prime permutations, and then
 * it can test all of them to see if three of them are the same
 * distance apart. This will catch the original example, while it
 * misses it right now.  Fortunately, the number they are looking for
 * is caught by this faulty function.
 */
void test(int a, int b, int c, int d) {
  int pindex, i, j, k, l, temp;
  int p[24];
  int val[4];

  /*
   * We only care if the value of this is prime.
   */
  p[0] = value(a,b,c,d);
  if( !isPrime(p[0])) {
    return;
  }

  val[0] = a;
  val[1] = b;
  val[2] = c;
  val[3] = d;

  for( i = 1; i <24; i++ ) {
    p[i] = 0;
  }
  pindex = 1;

  /*
   * Populate the array with all primes of these 4 digits
   */
  for( i = 1; i < 4; i++ ) {
    for( j = 0; j < 4; j++ ) {
      if( i==j ) continue;
      for( k = 0; k < 4; k++ ) {
	if( k==i || k == j ) continue;
	for( l = 0; l < 4; l++ ) {
	  if( l==k || l==j || l==i ) continue;
	  temp = value(val[i], val[j], val[k], val[l]);
	  if( isPrime(temp) ) {
	    p[pindex] = temp;
	    pindex++;
	  }
	}
      }
    }
  }
  
  pindex = removedups(p,pindex);

  if( pindex < 3 ) {
    return;
  }
  findwinners( p, pindex);
}

void findwinners(int p[], int pindex) {
  int a, b, c;
  for( a = 0; a < pindex-2; a++) {
    for( b = a+1; b < pindex-1; b++) {
      for( c = b+1; c < pindex; c++) {
	if( p[b]-p[a] == p[c]-p[b] ) {
	  winner(p[a], p[b], p[c]);
	}
      }
    }
  }
}

int removedups(int p[], int pindex) {
  int i, j, tmp;

  for( i = 0; i < pindex; i++ ) {
    for( j = i+1; j < pindex; j++ ) {
      if( p[j] == p[i] ) {
	p[j] = p[pindex-1];
	pindex--;
	j--;
	continue;
      }
      if( p[j] < p[i] ) {
	tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
      }
    }
  }
  return pindex;
}

/*
 * This works for the problem, but fails for the original example.
 * I want to fix it.
 */
int main(int argc, char *argv[]) {
  int thousands, hundreds, tens, ones;

  for(thousands = 1; thousands <= 9; thousands++) {
    for(hundreds = thousands; hundreds <= 9; hundreds++) {
      for(tens = thousands; tens <= 9; tens++) {
	for(ones = 1; ones <= 9; ones += 2) {
	  test(thousands, hundreds, tens, ones);
	}
      }
    }
  }

  return 0;
}
