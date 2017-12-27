#include <iostream>

long triangle(long a) {
  return (a * (a+1))/2;
}

int main() {
  long a=1, b= 86, c=86, d=0,e=0,f=0,g=0,h=0;
  
  for( a = a * 10; a != 0; a-- ) {
    b += c;
    c += b;
  }

  h = 1;
  for( f = 17; f > 0; f--) {
    h += h;
  }
  h--;

  std::cout << "A = 0: " << (86 * (2 * 86 - 86 + 1)) / 2 % h << std::endl;
  
  // This should be the same as below
  // std::cout << (b*(c+1) - triangle(b))%h << std::endl;

  // Combined into 1 line
  std::cout << "A = 1: " << (b * (2 * c - b + 1)) / 2 % h << std::endl;

  // This appears to be a variation of the triangular numbers
  d = 1;
  for( d = 1; d <= b; d++ ) {
    f += c - (d - 1);
    f %= h;
  }

  std::cout << "a: " << a << "\tb: " << b << "\tc: " << c
	    << "\td: " << d << "\te:  " << e << "\tf: "
	    << f << "\tg: " << g << "\th: " << h << std::endl;
  
  return 0;
}
