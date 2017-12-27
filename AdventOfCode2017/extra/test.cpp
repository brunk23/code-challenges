#include <iostream>

int main() {
  long b = 86, c = b, f = 17, h = 0;

  std::cout << "What should we use for b (86 default): ";
  if( !(std::cin >> b) || (b <= 0)  ) {
    b = 86;
  }

  std::cout << "set b " << b << std::endl;
  c = b;
  h = (1 << f) - 1;

  f = (b * (2 * c - b + 1)) / 2 % h;

  std::cout << "If A = 0: F = " << f << std::endl;

  b *= 10946;
  c *= 17711;

  f = (b * (2 * c - b + 1)) / 2 % h;

  std::cout << "If A = 1: F = " << f << std::endl;

  return 0;
}
