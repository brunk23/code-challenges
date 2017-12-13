#include <iostream>

// This one also works but is much slower than the array method
// This version:
//     0m06.43s real     0m06.48s user     0m00.01s system
// Array method:
//     0m00.21s real     0m00.22s user     0m00.01s system

using std::cout;
using std::endl;

const int GOAL = 34000000;

int sumfactors(const int n);

int main()
{
  int x = 1, y;
  
  while( (y=sumfactors(x)) == 0 ) {
    ++x;
  }

  cout << "The first house to get at least " << GOAL
       << " presents was house number " << y << endl;
  
  return 0;
}

int sumfactors(const int n )
{
  int total = 0;
  int x = 1;
  for(x = 1; (x*x) <= n; ++x ) {
    if( (n%x) == 0 ) {
      if( (50*x) >= n) {
	total += x;
      }
      if( n/x != x ) {
	if( ( 50 * (n/x) ) >= n ) {
	  total += n/x;
	}
      }
    }
  }
  
  if( (total * 11) >= GOAL ) {
    return n;
  }
  
  return 0;
}
