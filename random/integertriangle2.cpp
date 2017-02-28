/*
 * Find integer solutions for a triangle given the hypotenus
 */

#include <iostream>
#include <cmath>

void output_solution(int, int, int);
int find_solutions(int);

void output_solution(int a, int b, int c) {
  std::cout << "a: " << a << "\tb: " << b << "\tc: " << c << std::endl;
}

int find_solutions(int a) {
  int aPow2 = a * a;
  int c, b, cPow2, bPow2, max = 1000;
  for( b = 1; b < max; ++b ) {
    bPow2 = b * b;
    c = static_cast<int>(std::sqrt( static_cast<double>(bPow2 + aPow2) ));
    cPow2 = c * c;
    if( cPow2 == (bPow2 + aPow2) ) {
      output_solution(a, b, c);
      return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int a, solutions;
  std::cout << "Height: ";
  std::cin >> a;
  solutions = find_solutions(a);
  if( solutions > 0 ) {
    std::cout << "Found " << solutions << " solutions." << std::endl;
    return 0;
  } else {
    std::cout << "No valid integer solutions under 1000 found!" << std::endl;
  }
  return 1;
}
