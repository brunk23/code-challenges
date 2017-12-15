#include <iostream>

using std::cout;
using std::endl;

class Generator {
private:
  long factor;
  long modulus;
  long value;
  int divider;

public:
  Generator(long fact, int div, long seed) {
    modulus = 2147483647;     // Given by the problem
    factor = fact;
    value = seed;
    divider = div;
  }

  long next() {
    do {
      value *= factor;
      value %= modulus;
    } while( 0 != (value % divider) );

    return value;
  }
};

bool match(long, long);

bool match(long a, long b) {
  if( (a & 0xffff) == (b & 0xffff) ) {
    return true;
  }
  return false;
}

int main() {
  int i, count = 0;
  long avalue, bvalue;
  // Given by the problem set.
  //  Generator a(16807, 4, 65);
  //  Generator b(48271, 8, 8921);

  // Given by my specific input
  Generator a(16807, 4, 783);
  Generator b(48271, 8, 325);                                                                         

  for( i = 0; i < 5000000; i++ ) {
    avalue = a.next();
    bvalue = b.next();
    if( match(avalue, bvalue) ) {
      count++;
    }
  }

  cout << count << " total matches." << endl;

  return 0;
}
