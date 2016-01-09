#include <iostream>

/* Which prime under 1,000,000 can be expressed as
 * the longest sum of consecutive primes */

using std::cout;
using std::endl;

int s_of_E(int [], int);
int longest_length(int [], int, int);

int main()
{
  int numbers[1000000], x, y, max = 0, mstart = 0;

  /* Get a list of all the primes */
  s_of_E(numbers, 1000000);

  for(x = 0; x < 1000000; ++x) {
    if( numbers[x] ) {
      y = longest_length(numbers, x, 1000000);
      if( y >= max ) {
	max = y;
	mstart = x;
      }
    }
  }
  cout << "Longest found was the sum of " << max
       << " prime numbers." << endl;
  y = 0;
  while( max > 0 ) {
    if( numbers[mstart] ) {
      y += numbers[mstart];
      --max;
    }
    ++mstart;
  }

  cout << "It was " << y << endl;
  
  return 0;
}

int longest_length(int numbers[], int start, int max)
{
  int len = 0, x = 0, sum = 0, count = 0;
  for( x = start; x < max; ++x ) {
    if( numbers[x] ) {
      ++count;
      sum += numbers[x];
      if( (sum-2) < max ) {
	if( numbers[sum-2] ) {
	  len = count;
	}
      } else {
	break;
      }
    }
  }
  return len;
}

int s_of_E(int numbers[], int size)
{
  int x, y, f;

  for(x = 0; x < size; ++x) {
    numbers[x] = x+2;
  }

  /* could stop at sqrt(size), don't */
  for(x = 0; x < size; ++x) {
    if(numbers[x] > 0) {
      f = numbers[x];
      for( y = x+f; y < size; y += f ) {
	if( (numbers[y]%f) == 0 ) {
	  numbers[y] = 0;
	}
      }
    }
  }

  return 0;
}
