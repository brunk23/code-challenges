#include <iostream>

using namespace std;

bool isPrime(int);
bool righttrucatable(int);
bool lefttruncatable(int);

/*
 * An ugly but quick prime tester 
 */
bool isPrime(int number) {
  int n;
  if( number == 2 ) {
    return true;
  }
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

bool righttruncatable(int number) {
  while(number > 0) {
    if( !isPrime(number) || number == 1 ) {
      return false;
    }
    number /= 10;
  }
  return true;
}

bool lefttruncatable(int number) {
  int f = 10;
  while( f < number ) {
    f *= 10;
  }
  while( number ) {
    f /= 10;
    if( !isPrime(number) || number == 1 ) {
      return false;
    }
    number %= f;
  }
  return true;
}

int main(int argc, char *argv[]) {
  int n, count, sum;

  count = 1;
  sum = 0;
  for(n = 11; count < 12; n++ ) {
    if( righttruncatable(n) && lefttruncatable(n) ) {
      sum += n;
      cout << count << ": " << n << " (" << sum << ")" << endl;
      count++;
    }
  }
 
  return 0;
}
