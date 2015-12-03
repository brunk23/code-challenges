/*
 * Calculate needed wrapping paper
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int paper_needed(int, int, int);
int smallest_value(int, int, int);

int main() {
  int total_needed = 0, side[3] = {0,0,0};
  int input, sidenumb = 0;
  
  while ( (input = cin.get()) != EOF ) {
    switch ( input ) {
    case '0':
      side[sidenumb] = 10 * side[sidenumb] + 0;
      break;
    case '1':
      side[sidenumb] = 10 * side[sidenumb] + 1;
      break;
    case '2':
      side[sidenumb] = 10 * side[sidenumb] + 2;
      break;
    case '3':
      side[sidenumb] = 10 * side[sidenumb] + 3;
      break;
    case '4':
      side[sidenumb] = 10 * side[sidenumb] + 4;
      break;
    case '5':
      side[sidenumb] = 10 * side[sidenumb] + 5;
      break;
    case '6':
      side[sidenumb] = 10 * side[sidenumb] + 6;
      break;
    case '7':
      side[sidenumb] = 10 * side[sidenumb] + 7;
      break;
    case '8':
      side[sidenumb] = 10 * side[sidenumb] + 8;
      break;
    case '9':
      side[sidenumb] = 10 * side[sidenumb] + 9;
      break;
    case 'x':
    case 'X':
      sidenumb++;
      if( sidenumb > 2 ) {
	// This shouldn't happen... but treat it like a newline
	cout << "There shouldn't be 4 sides? Check your input." << endl;
	
	total_needed += paper_needed(side[0], side[1], side[2]);
	cout << "Total needed so far: " << total_needed << endl;

	side[0] = 0;
	side[1] = 0;
	side[2] = 0;
	sidenumb = 0;
      }
      break;
    case '\n':
      if ( sidenumb != 2 ) {
	cout << "There should be 3 sides! Check your input." << endl;
      }

      total_needed += paper_needed(side[0], side[1], side[2]);
      cout << "Total needed so far: " << total_needed << endl;      
      
      side[0] = 0;
      side[1] = 0;
      side[2] = 0;
      sidenumb = 0;
      break;
    default:
      // we ignore all other input.
      break;
    }
  }
  
  cout << "The total paper needed was " << total_needed << endl;
  
  return 0;
}

int smallest_value(int a, int b, int c)
{
  int small = a;
  if ( b < small ) {
    small = b;
  }
  if ( c < small ) {
    small = c;
  }
  cout << "The smallest value was " << small << endl;
  return small;
}

int paper_needed(int length, int width, int height)
{
  int area_lw, area_lh, area_wh, total;

  area_lw = length * width;
  area_lh = length * height;
  area_wh = width * height;

  total = 2 * ( area_lw + area_lh + area_wh) +
	   smallest_value(area_lw, area_lh, area_wh);

  cout << "Total for box " << length << "x" << width
       << "x" << height << " = " << total << endl;

  return total;
}
