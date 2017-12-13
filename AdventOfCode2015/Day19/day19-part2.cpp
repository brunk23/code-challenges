#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

#include "day19.h"

// Read the starting elements and the start string.
Element *read_input(Element **);

int main()
{
  Element *head=0;
  Element *start_string=0;
  
  head = read_input( &start_string );

  // ok, I needed help for this one. Brute force wasn't working
  // for the dataset I had, and I wasn't able to see the pattern
  // r/adventofcode/comments/3xflz8/day_19_solutions/cy4etju
  // explained it and gives the formula
  // (total_elements - (Rn + Ar) - 2*Y - 1)

  int x = 0;
  int total = 0;
  int RnAr = 0;
  int Y = 0;
  char curr;

  // loop until the end of the string
  while ( (curr=start_string->getName()[x]) != 0) {
    if( (curr >= 'A') && (curr <= 'Z') ) {
      // all elements start with capital letters
      ++total;
      if( curr == 'Y' ) {
	++Y;
      }
      if( curr == 'R' ) {
	++RnAr;
      }
      if( curr == 'A' && start_string->getName()[x+1] == 'r' ) {
	++RnAr;
      }
    }
    ++x;
  }

  // implement the formula given in the reddit answer, after performing
  // the count operation above.
  x = total - RnAr - 2*Y - 1;
  
  cout << endl << "Transformations: " << x << endl;
  return 0;
}


/*
 * This reads the input file into the crazy structure that I have.
 * This reads the elements backwards (because that was my previous
 * attempt).  At this point, my solution does not require the conversion
 * table any more, it just needs the start string.  This reads the table
 * anyway, because I didn't feel like reformatting this again.  I don't
 * use the returned value, just the start_string value, in the main
 * function
 */
Element *read_input(Element **start_string)
{
  Element *start = 0;
  string input;
  size_t offset = 0;
  
  while( getline(cin, input) ) {
    offset = input.find(" => ");
    if( offset != std::string::npos ) {
      if( start == 0 ) {
	start = new Element( input.substr(offset + 4).c_str() );
      } else {
	*start + input.substr(offset + 4).c_str();
      }
      start->addConverts( input.substr( offset + 4 ).c_str(),
			  input.substr( 0, offset ).c_str() );
    } else {
      if( (input[0] >='A' && input[0] <= 'Z') ||
	  (input[0] >='a' && input[0] <= 'z') ) {
	*start_string = new Element( input.c_str() );
      }
    }
  }
  return start;
}
