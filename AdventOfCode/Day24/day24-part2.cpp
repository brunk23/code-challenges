#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::setw;

#define TOT 29

int countnumb(int tried[TOT]);
bool sumarrays(int tried[TOT], int numbers[TOT], int foo);
long prod(int tried[TOT], int numbers[TOT]);
int incarray(int tried[TOT]);

int main()
{
  int numbers[TOT];
  int tried[TOT];
  int foo, xmax = 0;
  int x = TOT-1, total = 0;
  long temp, min = LONG_MAX, minprod = LONG_MAX;
  
  while( !cin.eof() ) {
    cin >> foo;
    if( cin.eof() ) {
      break;
    }
    numbers[x--] = foo;
    total += foo;
  }

  for(x = 0; x != TOT; ++x) {
    tried[x] = 0;
  }

  foo = total/4;
  x = 0;
  while( x < TOT ) {
    if( sumarrays(tried,numbers,foo) ) {
      temp = countnumb(tried);
      if( temp <= min ) {
	min = temp;
	temp = prod(tried,numbers);
	if( temp < minprod ) {
	  minprod = temp;
	  cout << "Current minproduct [" << xmax << "]: " << minprod << endl;
	}
      }
    }
    x = incarray(tried);
    if( x > xmax ) {
      xmax = x;
    }
  }
  
  cout << min << " numbers\n" << minprod << " product." << endl;
  return 0;
}

int incarray(int tried[TOT])
{
  int x;
  for(x = 0; x < TOT; ++x ) {
    if( tried[x] == 0 ) {
      tried[x] = 1;
      break;
    }
    tried[x] = 0;
  }
  return x;
}

int countnumb(int tried[TOT])
{
  int total = 0, n;
  for( n = 0; n < TOT; n++ ) {
    total += tried[n];
  }
  
  return total;
}

bool sumarrays(int tried[TOT], int numbers[TOT], int foo)
{
  int total = 0, n;
  for( n = 0; n < TOT; n++ ) {
    total += tried[n]*numbers[n];
  }

  return (total == foo);
}

long prod(int tried[TOT], int numbers[TOT])
{
  long total = 1, n;
  for( n = 0; n < TOT; n++ ) {
    if( tried[n] ) {
      total *= numbers[n];
    }
  }

  if( total < 0 ) {
    total = LONG_MAX;
  }
  return total;
}
