#include <iostream>

using std::cout;
using std::endl;

class Generator {
private:
  long factor;
  long modulus;
  long value;

public:
  Generator(long fact, long seed) {
    modulus = 2147483647;     // Given by the problem
    factor = fact;
    value = seed;
  }

  long next() {
    value *= factor;
    value %= modulus;
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
  //  Generator a(16807, 65);
  //  Generator b(48271, 8921);

  // Given by my specific input
  // Generator a(16807, 783);
  // Generator b(48271, 325);

  // Given by my specific input alt account
  Generator a(16807, 634);
  Generator b(48271, 301);                                                                         


  for( i = 0; i < 40000000; i++ ) {
    avalue = a.next();
    bvalue = b.next();
    if( match(avalue, bvalue) ) {
      count++;
    }
  }

  cout << count << " total matches." << endl;

  return 0;
}
