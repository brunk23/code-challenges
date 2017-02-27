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

int find_solutions(int c) {
  int cPow2 = c * c;
  int a, b, aPow2, bPow2, max = c;
  int solutions = 0;
  for( a = 1; a < max; ++a ) {
    aPow2 = a * a;
    b = static_cast<int>(std::sqrt( static_cast<double>(cPow2 - aPow2) ));
    bPow2 = b * b;
    if( cPow2 == (bPow2 + aPow2) ) {
      max = b;
      output_solution(a, b, c);
      solutions++;
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
