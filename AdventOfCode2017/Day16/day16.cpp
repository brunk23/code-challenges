#include <iostream>
#include <string>
#include "programs.h"
#include "command.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

void process(Programs &);

void process(Programs &prog) {
  string input;
  Command commands;
  unsigned int i;
  int a, b;
  char p, q;
  
  while( getline(cin, input) ) {
    for(i = 0; i < input.length(); i++ ) {
      if(input[i] == 'x' ) {
	i++;
	a = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  a *= 10;
	  a += input[i] - '0';
	  i++;
	}
	i++;
	b = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  b *= 10;
	  b += input[i] -'0';
	  i++;
	}
 
	commands.add(a,b);
	continue;
      }
      if( input[i] == 'p' ) {
	i++;
	p = input[i];
	i += 2;
	q = input[i];
	commands.add(p,q);
	continue;
      }
      if( input[i] == 's' ) {
	i++;
	a = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  a *= 10;
	  a += input[i] - '0';
	  i++;
	}
	commands.add(a);
	continue;
      }
    }
  }

  for( i = 0; i < 1000000000; i++ ) {
    commands.run(prog);
    if( prog.isRestart() ) {
      cout << "We repeat at " << i+1 << " steps so we only need "
	   << 1000000000 % (i+1) << " iterations." << endl;
      break;
    }
  }
  a = 1000000000 % (i+1);
  for( b = 0; b < a; b++ ) {
    commands.run(prog);
    if( b == 0 ) {
      cout << b+1 << ": " << prog << endl;
    }
  }
  cout << b << ": " << prog << endl;
}

int main() {
  static int NUMBER = 16;
  Programs a( NUMBER );

  process(a);

  return 0;
}
