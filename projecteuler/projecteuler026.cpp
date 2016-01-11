#include <iostream>

using namespace std;


/*
 * Find length of repeating part of decimal
 */
int repeating_part(int);

int main()
{
  int x = 0, y = 0, d = 0, max = 0;

  for( x = 2; x <= 1000; ++x ) {
    y = repeating_part(x);
    if( y > max ) {
      max = y;
      d = x;
    }
  }

  cout << "1/" << d << " was the highest with "
       << max << " repeating digits." << endl;
  return 0;
}

int repeating_part(int d) {
  int remain[1000];
  int index = 0;
  int a, b;

  a = 1;
  
  while( a ) {
    a *= 10;
    a = a % d;
    
    if( !a ) {
      return 0;
    }

    remain[index++] = a;
    for( b = index-2; b >= 0; --b ) {
      if( remain[b] == a ) {
	return (index - 1 - b);
      }
    }
  }
  return 0;
}
