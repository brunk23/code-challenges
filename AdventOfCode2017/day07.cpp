#include <iostream>
#include <string>

#define NUMBER 1089

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::readline;

/*
 * Each node will have a name and weight
 * It will hold a list of what is below it
 * Next is the one on the same level
 */
struct Node {
  string name;
  int weight;
  int totalWeight;
  string holds[10];
};

bool strequal(string, string);

bool strequal( string a, string b ) {
  int i;
  if( a.length() != b.length() ) {
    return false;
  }
  for( i = 0; i < a.length(); i++) {
    if( a[i] != b[i] ) {
      return false;
    }
  }
  return true;
}

/*
 * Returns true if the line parsed correctly
 */
bool parseLine(string line, Node n[NUMBER], int loc) {
  string curr;
  int w, i, count = 0, state = 0;

  n[loc].totalWeight = -1;
  for( i = 0; i < line.length(); i++ ) {
    

  }


  return true;
}

int main() {
  Node n[NUMBER];
  string line;
  int i = 0;

  while( readline(cin, line) ) {
    if( !(parseLine( line, n, i )) ) {
      cerr << "Cound not parse line: " << line << endl;
      return 1;
    }
    i++;
  }

}
