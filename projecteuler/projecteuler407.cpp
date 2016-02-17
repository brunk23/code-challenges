#include <iostream>

using namespace std;

inline long M(long);
inline long y(long,long);

int main() {
  long i, sum = 0, temp;
  for( i = 1; i <= 10000000; ++i ) {
    temp = M(i);
    sum += temp;
    cout << i << ": " << temp << endl;;
  }
  cout << sum << endl;

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
