#include <iostream>

using namespace std;

inline long M(long);
inline long y(long,long);

int main() {
  cout << M(6) << endl;

  return 0;
}

inline long M(long a) {
  long max = 0;
  long i, tmp;

  for( i = 1; i < a; i++ ) {
    tmp = y(i, a);
    if( tmp > max ) {
      max = tmp;
    }
  }

  return max;
}

inline long y(long a, long n) {
  return (a*a) % n;
}
