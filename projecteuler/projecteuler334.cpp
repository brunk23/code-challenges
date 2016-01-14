#include <iostream>

using namespace std;

/*
 * Plato's Heavenly Beans
 */

int t(int);
int b(int);

/*
 * Demonstrate that these return the right values
 * Now I need to figure out how to use them to solve
 * the number of moves
 */
int main()
{
  cout << "b1: " << b(1) << endl
       << "b2: " << b(2) << endl;

  cout << "t1: " << t(1) << endl
       << "t2: " << t(2) << endl;

  
  return 0;
}

/*
 * Implement b_subi function from description
 */
int b(int i) {
  return (t(i) % 2048) + 1;
}

/*
 * Implement t_subi function from description
 */
int t(int i) {
  int ti;
  
  if( i == 0 ) {
    return 123456;
  }
  ti = t(i-1);
  if( ti % 2 == 0 ) {
    return ti / 2;
  }
  
  return ((ti / 2) ^ 926252);
}
