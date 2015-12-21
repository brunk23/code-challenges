#include <iostream>

// today is easy, it's just a factorization puzzle

using std::cout;
using std::endl;

const int GOAL = 34000000;

int sumfactors(int n);

int main()
{
  int x = 1;
  int end = GOAL/10; // each house gets 10 per elf
  
  while( true ) {
    if( sumfactors(x) >= end ) {
      break;
    }
    ++x;
  }

  cout << "The first house to get at least " << GOAL
       << " presents was house number " << x << endl;
  
  return 0;
}


int sumfactors( int n )
{
  int total = 0;
  
  for(int x = 1; (x*x) <= n; ++x ) {
    if( (n%x) == 0 ) {
      total += x;
      if( (n/x) != x ) {
	total += n/x;
      }
    }
  }

  return total;
}
