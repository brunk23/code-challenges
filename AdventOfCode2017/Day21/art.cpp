#include <string>
#include "art.h"

Art::Art(int n) : size(n)
{
  int i,j;
  pic = new char[size*size];
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      pic[i * size + j] = '.';
    }
  }
}

Art::~Art() {
  delete pic;
}

void Art::fill(std::string s) {
  unsigned int i;
  if( s.length() < (size * size) ) {
    std::cerr << "String does not fill pic." << std::endl;
    return;
  }
  for( i = 0; i < (size * size); i++ ) {
    pic[i] = s[i];
  }
}

int Art::pixels() {
  unsigned int i;
  int count = 0;
  for( i = 0; i < (size * size); i++ ) {
    if( pic[i] == '#' ) {
      count++;
    }
  }
  return count;
}

std::string Art::box2(int x, int y) {
  std::string a = "";

  return a;
}

std::string Art::box3(int x, int y) {
  std::string a = "";

  return a;
}

std::ostream& operator<<(std::ostream& os, const Art& s) {
  unsigned int i, j;

  for( i = 0; i < s.size; i++ ) {
    for(j = 0; j < s.size; j++ ) {
      os << s.pic[i * s.size + j];
    }
    os << std::endl;
  }
  return os;
}
