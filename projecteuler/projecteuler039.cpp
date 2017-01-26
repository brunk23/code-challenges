#include <iostream>

using std::cout;
using std::endl;

int integersolutions(int n) {
  int count = 0;

  // We will test all a, b
  int a, b, c;
  
  for(a = 1; a < n; ++a) {
    for(b = a; b < (n-a); ++b) {
      c = n - (a + b);
      if( a*a + b*b == c*c ) {
	++count;
      }
    }
  }
  return count;
}


int main(int argc, char *argv[]) {
  int max;
  int which;
  int curr;
  int i;

  for(i = 3; i <= 1000; ++i) {
    curr = integersolutions(i);
    cout << i << ": " << curr << endl;
    if( curr > max ) {
      which = i;
      max = curr;
    }
  }

  cout << endl << which << ": " << max << endl;

  return 0;
}

