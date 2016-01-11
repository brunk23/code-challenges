#include <iostream>

using namespace std;

/* The sum of the four corners of each
 * square is given by 4*x^2 - 6*(x-1).
 * after that it's just adding the 4
 * corners for each square 3-1001
 */

int main() {
  int x;
  int total = 1;
  
  for( x = 3; x <= 1001; x += 2 ) {
    total += (4*x*x - 6*(x-1));
  }

  cout << "Total is: " << total << endl;

  return 0;
}
