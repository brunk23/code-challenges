#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;
using std::getline;

#define NUMBER 2000
#define MAXWIRE 10

class Prog {
public:
  bool visited;
  int wires[MAXWIRE];
  
  Prog() {
    int i;
    visited = false;
    for( i = 0; i < MAXWIRE; i++ ) {
      wires[i] = -1;
    }
  }
  
  ~Prog() {
  }
};

bool isValid(int);
void visit(Prog a[NUMBER], int dest);

bool isValid(int i) {
  if( i >= 0 && i < NUMBER ) {
    return true;
  }
  return false;
}

void visit(Prog a[NUMBER], int dest) {
  int i;
  if( a[dest].visited ) {
    return;
  }
  a[dest].visited = true;
  for(i = 0; i < MAXWIRE; i++ ) {
    if( a[dest].wires[i] > -1 ) {
      visit(a, a[dest].wires[i]);
    }
  }
}

int main() {
  Prog a[NUMBER];
  string input;
  int i, value, j;

  while( getline(cin, input) ) {
    for( i = 0; i < input.length(); i++ ) {
      if( !( (input[i]>='0') && (input[i]<='9') ) ) {
	input[i] = ' ';
      }
    }
    stringstream s(input);
    if( !( s >> i ) ) {
      cerr << "What the heck! " << input << endl;
      return 1;
    }
    if( !isValid(i) ) {
      cerr << "Not a valid index. " << input << endl;
      return 1;
    }
    j = 0;
    while( s >> value ) {
      if( isValid(value) ) {
	a[i].wires[j] = value;
	j++;
      } else {
	cerr << "Not a valid index. " << input << endl;
      }
    }
  }

  visit(a,0);
  j = 0;
  for( i = 0; i < NUMBER; i++ ) {
    if( a[i].visited ) {
      j++;
      cout << "Visited: " << i << endl;
    }
  }

  cout << "Total visited " << j << endl;

  return 0;
}
