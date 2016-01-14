#include <iostream>

using namespace std;


bool isbouncy(int);

int main()
{
  long bouncy = 0, notbouncy = 0;
  int i;
  bool f90 = false, f50 = false;

  for( i = 1; i < 2200000; ++i ) {
    if( isbouncy(i) ) {
      bouncy++;
    } else {
      notbouncy++;
    }
    if( bouncy == notbouncy && !f50 ) {
      cout << "Equal at: " << i << endl;
      f50 = true;
    }
    if( bouncy == notbouncy*9 && !f90 ) {
      cout << "90% at: " << i << endl;
      f90 = true;
    }
    if( bouncy == notbouncy*99 ) {
      cout << "99% at: " << i << endl;
      break;
    }
  }

  return 0;
}

/*
 * Returns true if the number is bouncy, that is
 * the digits aren't strictly increasing or
 * decreasing. We return true as soon as we see a
 * digit that goes in the wrong opposite direction
 * of what we have been going.
 */
bool isbouncy(int n)
{
  int increasing = 0;
  int prev = -1, curr;

  while( n > 0 ) {
    if( prev >= 0 ) {
      curr = n % 10;
      if( curr > prev ) {
	if( increasing < 0 ) {
	  return true;
	}
	increasing = 1;
      } else {
	if( curr < prev ) {
	  if( increasing > 0 ) {
	    return true;
	  }
	  increasing = -1;
	}
      }
      prev = curr;
      n /= 10;
    } else {
      prev = n % 10;
      n /= 10;
    }
  }

  return false;
}
