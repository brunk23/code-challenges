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
  int number = 107900, upper;
  int count = 0;

  std::cout << "What's your input's initial b: ";
  std::cin >> number;

  std:: cout << "Part a: " << (number-2)*(number-2) << std::endl;

  number *= 100;
  number += 100000;
  upper = number + 17000;

  while( number <= upper ) {
    if( !isPrime(number)) {
      count++;
    }
    number += 17;
  }

  std::cout << "Part b: " << count << std::endl;
  
  return 0;
}
