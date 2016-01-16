#include <iostream>

using namespace std;

typedef long long vtype;

vtype tri(vtype);
vtype pen(vtype);
vtype hex(vtype);

int main() {
  vtype t = 285, p = 165, h = 143;
  vtype np, nh, tsum, psum, hsum;

  for( ++t ; t < 1000000; ++t ) {
    tsum = tri(t);
    np = p;
    while( (psum=pen(np)) < tsum ) {
      ++np;
    }
    if( psum == tsum ) {
      nh = h;
      while( (hsum=hex(nh)) < tsum ) {
	++nh;
      }
      if( hsum == tsum ) {
	cout << "Found a hit: " << tsum << " at t("
	     << t << ") p(" << np << ") h(" << nh
	     << ")" << endl;
	break;
      }
    }
  }

  return 0;
}

vtype tri(vtype n) {
  return (n*(n+1)/2);
}

vtype pen(vtype n) {
  return (n*(3*n-1)/2);
}

vtype hex(vtype n) {
  return (n*(2*n-1));
}
