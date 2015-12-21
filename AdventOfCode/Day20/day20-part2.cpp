#include <iostream>

using std::cout;
using std::endl;

const int GOAL = 34000000;
// Thanks to an incorrect previous answer, we know the correct
// answer is less than 1,000,000;
const int MAX = 1000000;

int visithouses(const int n,int a[MAX]);

int main()
{
  int x, y;
  int a[MAX];

  for( x = 0; x < MAX; ++x ) {
    a[x] = 0;
  }

  x = 1;
  
  while( (y = visithouses(x,a)) == 0 ) {
    ++x;
  }

  cout << "The first house to get at least " << GOAL
       << " presents was house number " << y << endl;
  
  return 0;
}

// I originally was limiting each house to 50 visits (first
// 50 factors), but that wasn't the problem description.
// Elf number 1 only visits houses 1-50.  Elf #2 visits just
// 2-100 (the evens only), and so on.  
// returns true if we need to keep visiting houses
int visithouses(const int n, int a[MAX])
{
  for(int x = 1; x <= 50; ++x ) {
    if( x*n < MAX ) {
      a[x*n] += 11*n;
      if( a[x*n] >= GOAL ) {
	return x*n;
      }
    }
  }
  
  return 0;
}
