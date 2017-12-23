#include <iostream>

bool isPrime(int a) {
  int fact = 3;

  if( a % 2 == 0 ) {
    return false;
  }
  while( fact*fact <= a ) {
    if( a%fact == 0 ) {
      return false;
    }
    fact += 2;
  }
  return true;
}

int main() {
  int number = 107900;
  int count = 0;
  
  while( number <= 124900 ) {
    if( !isPrime(number)) {
      count++;
    }
    number += 17;
  }

  std::cout << count << std::endl;
  
  return 0;
}
