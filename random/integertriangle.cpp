/*
 * Find integer solutions for a triangle given the hypotenus
 */

#include <iostream>

void output_solution(int, int, int);
int find_solutions(int);

void output_solution(int a, int b, int c) {
  std::cout << "a: " << a << "\tb: " << b << "\tc: " << c << std::endl;
}

/*
 * I could avoid using the second loop if I did sqrt(cPow2-aPow2)
 * and checked if that was an integer solution. But, for small values
 * of c, I am not sure if that will be faster than this method. More
 * testing for optimization should be done.
 */
int find_solutions(int c) {
  int cPow2 = c * c;
  int a, b, aPow2, bPow2;
  int solutions = 0;
  for( a = 1; a < c; ++a ) {
    for( b = a; b < c; ++b ) {
      aPow2 = a * a;
      bPow2 = b * b;
      if( cPow2 == (bPow2 + aPow2) ) {
	output_solution(a, b, c);
	solutions++;
      }
    }
  }
  return solutions;
}

int main(int argc, char *argv[]) {
  int c, solutions;
  std::cout << "Hypotenus: ";
  std::cin >> c;
  solutions = find_solutions(c);
  if( solutions > 0 ) {
    std::cout << "Found " << solutions << " solutions." << std::endl;
    return 0;
  } else {
    std::cout << "No valid integer solutions found!" << std::endl;
  }
  return 1;
}
