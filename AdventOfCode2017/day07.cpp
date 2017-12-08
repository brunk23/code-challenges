#include <iostream>
#include <string>

#define NUMBER 1089

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::cerr;

/*
 * Each node will have a name and weight
 * It will hold a list of what is below it
 * Next is the one on the same level
 */
struct Node {
  string name;
  int weight;
  int totalWeight;
  int holding;
  string holds[10];
};

bool strequal(string, string);
bool parseLine(string, Node, int);
int parseNumber(string);

int weight(Node n[NUMBER], int i) {
  int j, k, weights[10], index[10];

  if( n[i].totalWeight > 0 ) {
    return n[i].totalWeight;
  }
  if( n[i].holding == 0 ) {
    n[i].totalWeight = n[i].weight;
    return n[i].weight;
  }
  for(j = 0; j < n[i].holding; j++) {
    for(k = 0; k < NUMBER; k++) {
      if( n[k].name == n[i].holds[j] ) {
	index[j] = k;
	if( -1 == (weights[j] = weight(n, k) ) ) {
	  return -1;
	}
	break;
      }
    }
  }
  if( n[i].holding == 1 ) {
    n[i].totalWeight = weights[0] + n[i].weight;
    return n[i].totalWeight;
  }
  n[i].totalWeight = n[i].weight;
  for( j = 0; j < n[i].holding; j++ ) {
    n[i].totalWeight += weights[j];
    if( j > 0 ) {
      if( weights[j] == weights[j-1] ) {
	continue;
      } else {
	cout << "Found the unbalanced branch\n\n";
	cout << "Name\tWeight\tTotal weight\n";
	cout << "----\t------\t------------\n";
	for( j = 0; j < n[i].holding; j++ ) {
	  cout << n[index[j]].name << "\t" << n[index[j]].weight
	       << "\t" << n[index[j]].totalWeight << endl;
	}
	return -1;
      }
    }
  }
  return n[i].totalWeight;
}

bool strequal( string a, string b ) {
  unsigned int i;
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

int parseNumber(string s) {
  int total = 0;
  unsigned int i = 1;
  while( s[i] != ')' ) {
    total *= 10;
    total += s[i] - '0';
    i++;
  }
  return total;
}

/*
 * Returns true if the line parsed correctly
 */
bool parseLine(string line, Node n[NUMBER], int loc) {
  string curr;
  int count = 0, state = 0;
  unsigned int i=0, prev=0;

  n[loc].totalWeight = -1;
  for( i = 0; i < line.length(); i++ ) {
    if( line[i] != ' ' ) {
      continue;
    }
    if( state == 0 ) {
      n[loc].name = line.substr(0,i);
      state = 1;
      prev = i + 1;
      continue;
    }
    if( state == 1 ) {
      n[loc].weight = parseNumber(line.substr(prev, i - prev));
      prev = i + 1;
      state = 2;
      continue;
    }
    if( line[prev] == '-' ) {
      prev = i + 1;
      continue;
    }
    // Add sub node
    n[loc].holds[count] = line.substr(prev, i - prev - 1);
    count++;
    prev = i + 1;
  }
  if( state == 1 ) {
    n[loc].weight = parseNumber(line.substr(prev, i - prev));
  } else{
    // Add sub node
    n[loc].holds[count] = line.substr(prev, i - prev);
    count++;
  }
  n[loc].holding = count;
  return true;
}

int main() {
  Node n[NUMBER];
  string line, start = "dgoocsw";
  int i = 0, begin;

  while( getline(cin, line) ) {
    if( !(parseLine( line, n, i )) ) {
      cerr << "Cound not parse line: " << line << endl;
      return 1;
    }
    if( strequal( start, n[i].name ) ) {
	begin = i;
    }
    i++;
  }

  weight(n, begin);
  
  return 0;
}
