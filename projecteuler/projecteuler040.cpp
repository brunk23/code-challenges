#include <iostream>

using std::cout;
using std::endl;

int populate(int [], int);

/* populates array, returns number of digits */
int populate(int digitarray[], int number) {
  int index = 0;
  while( number > 0 ) {
    digitarray[index] = number % 10;
    number /= 10;
    index++;
  }
  return index;
}

int main() {
  int digits[8];
  int i, j;
  int totalDigits = 0;
  int product = 1;

  for( i = 0; i < 8; i++ ) {
    digits[i] = 0;
  }

  for( i = 1; totalDigits <= 1000000; i++ ) {
    for( j = (populate(digits, i) - 1); j >= 0; --j ) {
      totalDigits++;
      if( totalDigits == 1       || totalDigits == 10      || totalDigits == 100    ||
	  totalDigits == 1000    || totalDigits == 10000   || totalDigits == 100000 ||
	  totalDigits == 1000000 ) {
	product *= digits[j];
      }
    }
  }
    
  cout << "Product: " << product << endl;

  return 0;
}
