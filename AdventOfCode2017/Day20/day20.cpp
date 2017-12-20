#include <iostream>
#include <string>
#include "particle.h"

using std::cin;
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cerr;

#define NUMBER 1000

int main() {
  Particle list[NUMBER];
  string input;
  int n = 0, change, number;

  /*
   * Read in the input file
   */
  while( getline(cin, input) ) {
    if( list[n].parseDef(input) != 0 ) {
      cerr << "Error parsing: " << input << endl;
      return 1;
    }
    n++;
  }
  number = 0;
  change = list[0].changeA();
  for( n = 1; n < NUMBER; n++ ) {
    if( list[n].changeA() <= change ) {
      if( list[n].changeA() != change ||
	  ( list[n].changeV() < list[number].changeV() )) {
	change = list[n].changeA();
	number = n;
      }
    }
  }
  
  cout << "Number " << number << " stays closest." << endl;

  while(number > 448) {
    for(n = 0; n < NUMBER; n++ ) {
      list[n].update();
    }
    number = 0;
    for(n = 0; n < NUMBER; n++ ) {
      if( list[n].exists() ) {
	for( change = n+1; change < NUMBER; change++ ) {
	  if( list[n] == list[change] ) {
	    list[change].die();
	    list[n].die();
	  }
	}
      }
      if( list[n].exists() ) {
	number++;
      }
    }
  }
  cout << "Still have " << number << endl;
    
  return 0;
}
