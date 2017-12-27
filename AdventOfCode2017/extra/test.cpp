#include <iostream>

int main() {
  long a = 0, b = 86, c = b, f = 17, h = 0;

  if( a != 0 ) {
    b *= 10946;
    c *= 17711;
  }

  h = (1 << f) - 1;

  // Combined into 1 line
  std::cout << "A = " << a << ": " << (b * (2 * c - b + 1)) / 2 % h << std::endl;
  
  return 0;
}
