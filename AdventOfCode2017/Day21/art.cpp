#include <string>
#include "art.h"
#include "tlist.h"

Art::Art(int n, TList *x) : size(n)
{
  int i,j;
  t = x;
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

unsigned int Art::nextsize() {
  if( (size % 2) == 0 ) {
    return size+size/2;
  }
  if( (size % 3) == 0 ) {
    return size+size/3;
  }
  std::cerr << "New size failed." << std::endl;
  return 2;
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

void Art::fill(int x, int y, std::string s) {
  int fact = -1;
  unsigned int i, j;
  if( s.length() == 9 ) {
    if( (size % 3) == 0 ) {
      fact = 3;
    } else {
      fact = -1;
    }
  } else {
    if( s.length() == 16 ) {
      if( (size % 4) == 0 ) {
	fact = 4;
      } else {
	fact = -1;
      }
    }
  }
  if( fact == -1 ) {
    std::cerr << "BAD FILL LENGTH" << std::endl;
    return;
  }
  for( i = 0 ; i < fact; i++ ) {
    for( j = 0; j < fact; j++ ) {
      pic[(x*fact+i)*size + y*fact+j] = s[i*fact + j];
    }
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
