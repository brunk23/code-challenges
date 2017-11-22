/***
 * This is the master program for one of the challenges for
 * the programming club. It answers all the questions for
 * part 1, part 2, and provides output for the sample given
 * in the problem set.
 ***/
#include <iostream>

int sumFactorsTo(int, int);
int printcombo(int, int, int);
int allfactors(int, int, int);

using std::cout;
using std::endl;

/*
 * This is the O(1) solution for finding the sum of all
 * multiples of a number up to a given limit.
 */
int sumFactorsTo(int factor, int limit) {
  int a = limit / factor;
  return (factor * (a * (a + 1) ) /2);
}

/*
 * This is the O(1) solution for finding the union of all
 * multiples of two different numbers up to a given limit.
 */
int printcombo(int factor1, int factor2, int limit) {
  int a = 0;
  a = sumFactorsTo(factor1, limit);
  a += sumFactorsTo(factor2, limit);
  a -= sumFactorsTo(factor1 * factor2, limit);
  cout << "sumFactors(" << factor1 << "," << factor2 << ") to ";
  cout << limit << " = " << a << endl;
  return a;
}

/*
 * This is the O(n) solution for finding the union of all
 * the multiples of two different numbers, up to a given limit.
 * It also outputs all the numbers. This is used for the sample
 * problem only, because of the small limit.
 *
 * Technically, all the problems' limits are small enough to use
 * this in a reasonable amount of runtime. But, I like to have the
 * "real" solution proven.
 */
int allfactors(int f1, int f2, int limit) {
  int n, sum = 0;
  for(n = 1; n <= limit; n++) {
    if( ((n%f1) == 0) || ((n%f2) == 0) ) {
      sum += n;
      cout << n << "  ";
    }
  }
  cout << " = " << sum << endl;
  return 0;
}

/*
 * Output the three problem sets needed.
 */
int main(int argc, char *argv[]) {
  allfactors(3,5,38);
  printcombo(3,5,500);
  printcombo(2,7,1000);
  return 0;
}
