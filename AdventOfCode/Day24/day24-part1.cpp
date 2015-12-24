#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::setw;

#define TOT 29

int find_min(int numbers[TOT], int goal);
long min_QE(int numbers[TOT], int goal, int maxd, int depth, long prod, int sum);

int main()
{
  int numbers[TOT];
  int foo;
  int x = 0, total = 0;
  
  while( !cin.eof() ) {
    cin >> foo;
    if( cin.eof() ) {
      break;
    }
    numbers[x++] = foo;
    total += foo;
  }

  foo = total/3;

  x = find_min(numbers, foo);

  cout << "Min number of presents is: " << x << endl;

  return 0;
}

int find_min(int numbers[TOT], int goal)
{
  int y, n[TOT], sum = 0, packs = 0;
  long product = 1;
  
  for(y = TOT-1; y >=0 ; --y) {
    n[y] = 0;
  }
    
  for(y = 0; y < TOT ; ++y) {
    if( (sum + numbers[y]) <= goal ) {
      sum += numbers[y];
      n[y] = numbers[y];
      packs++;
    } else {
      n[y] = 0;
    }
    if( sum == goal ) {
      break;
    }
    if(y == 0) {
      // Still not found... go back up and get rid of
      // highest number used
      while( n[y] == 0 ) {
	y--;
      }
      n[y] = 0;
    }
  }

  for(y = 0; y < TOT; ++y) {
    if(n[y]) {
      cout << n[y] << " ";
    }
  }
  cout << endl;
  
  return packs;
}

long min_QE(int numbers[TOT], int goal, int maxd, int depth, long prod, int sum)
{
  int y;
  long pr = LONG_MAX, prtemp;
  /* Quit after maxd */
  if( depth > maxd || sum > goal ) {
    return pr;
  }

  cout << sum << "\t";
  prtemp = pr;
  int n[TOT];
  
  for( y = 0; y < TOT; ++y ) {
    n[y] = numbers[y];
  }

  if( depth < maxd ) {
    for( y = TOT-1; y >=0; --y ) {
      if( n[y] != 0 ) {
	n[y] = 0;
	prtemp = min_QE(n, goal, maxd, depth+1, prod*numbers[y], sum+numbers[y]);
	n[y] = numbers[y];
	if( prtemp < pr ) {
	  pr = prtemp;
	}
      }
    }
  } else {
    for( y = TOT-1; y >= 0; --y) {
      if( sum+numbers[y] == goal ) {
	prtemp = prod * numbers[y];
	if( prtemp < pr ) {
	  pr = prtemp;
	}
      }
    }
  }

  return pr;
}
