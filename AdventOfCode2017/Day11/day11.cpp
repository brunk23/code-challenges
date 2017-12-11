#include <iostream>
#include <sstream>
#include <string>

using std::endl;
using std::cin;
using std::cout;
using std::stringstream;
using std::string;

bool strequal(string, string);

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

class Location {
private:
  int x;
  int y;
  int z;

  int abs(int a) {
    if( a < 0 ) {
      a *= -1;
    }
    return a;
  }

public:
  Location() {
    x = 0;
    y = 0;
    z = 0;
  }

  Location(int a, int b, int c) {
    x = a;
    y = b;
    z = c;
  }

  Location(const Location &a) {
    x = a.x;
    y = a.y;
    z = a.z;
  }

  ~Location() {
  }

  // Movement
  void n() {
    x++;
    z--;
  }

  void nw() {
    x++;
    y--;
  }

  void ne() {
    y++;
    z--;
  }

  void s() {
    x--;
    z++;
  }

  void sw() {
    y--;
    z++;
  }

  void se() {
    x--;
    y++;
  }
  
  int distance(const Location &a ) {
    return (abs(x - a.x) + abs(y - a.y) + abs( z - a.z))/2;
  }

  friend std::ostream &operator<<(std::ostream &os, const Location &a) {
    return os << "x:" << a.x << " y:" << a.y << " z:" << a.z;
  }

};

int main() {
  Location start;
  Location curr(start);
  string input, dir;
  unsigned int i, max = 0;

  while( cin >> input ) {
    for( i = 0; i < input.length(); i++ ) {
      if( input[i] == ',' ) {
	input[i] = ' ';
      }
    }
    stringstream s(input);
    while( s >> dir ) {
      if( curr.distance(start) > max ) {
	max = curr.distance(start);
      }
      if( strequal( "n", dir ) ) {
	curr.n();
	continue;
      }
      if( strequal( "ne", dir ) ) {
	curr.ne();
	continue;
      }
      if( strequal( "nw", dir ) ) {
	curr.nw();
	continue;
      }
      if( strequal( "s", dir ) ) {
	curr.s();
	continue;
      }
      if( strequal( "se", dir ) ) {
	curr.se();
	continue;
      } 
      if( strequal( "sw", dir ) ) {
	curr.sw();
	continue;
      }
      cout << "Garbage in stream: " << dir << endl;
    }
  }

  cout << "Starting location: " << start << endl;
  cout << "Current location: " << curr << endl;
  cout << "Current distance away: " << curr.distance(start) << endl;
  cout << "Furthest distance away: " << max << endl;

  return 0;
}
