#include <iostream>

using std::cout;
using std::endl;

int rotate(int a);
bool testNum(int a);
bool isPrime(int a);

bool isPrime(int a) {
  int factor = 3;

  if( a == 2 ) {
    return true;
  }

  if( (a < 2) || ( (a % 2) == 0) ) {
    return false;
  }

  while( (factor*factor) <= a ) {
    if( 0 == (a % factor) ) {
      return false;
    }
    factor += 2;
  }

  return true;
}

int rotate(int a) {
  int right, div = 1;

  right = a % 10;
  a /= 10;

  while( a >= div ) {
    div *= 10;
  }
  a += (div * right);

  return a;
}

bool testNum(int a) {
  int curr = a;

  if( !isPrime(a) ) {
    return false;
  }

  curr = rotate(curr);
  while( curr != a ) {
    if( !isPrime(curr) ) {
      return false;
    }
    curr = rotate(curr);
  }

  return true;
}

int main() {
  int i, count = 0;

  for( i = 2; i < 1000000; i++ ) {
    if( testNum(i) ) {
      count++;
    }
  }

  cout << "There were " << count << " circular primes." << endl;

  return 0;
}

  
