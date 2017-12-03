#include <iostream>

using namespace std;

int newsquares(int);
int abs(int);

int abs(int n) {
  if( n < 0 ) {
    return n * -1;
  }
  return n;
}

int newsquares( int length ) {
  return ( 4 * length + 4 );
}

int main() {
  int goal;
  int s, e, len, mid;
  s = e = len =1;
  // goal = 347991;
  goal = 19;

  cin >> goal;

  while( e < goal ) {
    s = e +1;
    e += newsquares(len);
    len += 2;
  }
  cout << "Length: " << len << "\tMin: " << s
       << "\tMax: " << e << endl;
  // Where is goal
  mid = len/2;
  cout << mid + abs(((goal-s)%(len-1))+1-mid) << endl;
  
  return 0;
}
