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
    factor = fact;            // Diff for each object, given in problem
    value = seed;             // Individual to each user
    divider = div;            // Part of the new problem description
  }

  /*
   * Generate the next number according to the updated rules
   * for part b.
   */
  long next() {
    do {
      value *= factor;
      value %= modulus;
    } while( 0 != (value % divider) );

    return value;
  }

  /*
   * Overload == to perform the match operation. This removes
   * the need for extra variables and contains this method with
   * the object definition.
   */
  bool operator==(const Generator &rhs) {
    if( (value & 0xffff) == (rhs.value & 0xffff) ) {
      return true;
    }
    return false;
  }
};

int main() {
  int i, count = 0;
  // Given by the problem set.
  //  Generator a(16807, 4, 65);
  //  Generator b(48271, 8, 8921);

  // Given by my specific input
  Generator a(16807, 4, 783);
  Generator b(48271, 8, 325);                                                                         

  for( i = 0; i < 5000000; i++ ) {
    a.next();
    b.next();
    if( a == b ) {
      count++;
    }
  }

  cout << count << " total matches." << endl;

  return 0;
}
