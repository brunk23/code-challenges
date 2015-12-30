#include <iostream>

using std::cout;
using std::endl;

// Original:           0m00.60s real     0m00.56s user     0m00.00s system
// With inline -O2:    0m00.25s real     0m00.22s user     0m00.00s system


long triangle_number(long n);
int which_number(int row, int col);
long generate_code(long x);

int main()
{
  long start = 27995004, next;
  int x = 0, lower, upper;
  
  // The number at row n, col b is the number of
  // triangle_number(b) + triangle_number(b+n-2) - triangle_number(b-1)

  lower = which_number(6,6);
  upper = which_number(3010,3019);
  
  next = start;
  for( x = lower; x < upper; ++x) {
    next = generate_code(next);
  }

  cout << "The next code is: " << next << endl;
  
  return 0;
}

inline long generate_code(long inp)
{
  long temp;
  temp = inp * 252533;
  temp %= 33554393;
  return temp;
}

inline int which_number(int row, int col)
{
  return ( triangle_number(col) + triangle_number(col + row - 2)
	  - triangle_number(col - 1) );
}

// These are triangular numbers.
inline long triangle_number(long n)
{
  return (n*(n+1)/2);
}
