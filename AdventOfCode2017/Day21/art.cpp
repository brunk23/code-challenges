#include <string>
#include "art.h"
#include "tlist.h"

Art::Art(int n, TList *x) : size(n)
{
  int i,j;
  t = x;
  pic = new char[size*size];
  npic = 0;
  nsize = 0;
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      pic[i * size + j] = '.';
    }
  }
}

Art::~Art() {
  delete pic;
}

/*
 * Public: Fill with initial contents
 */
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

/*
 * Will make the new object.
 */
void Art::transform() {
  int n, i, j;
  std::string old, trns;
  nsize = nextsize();
  npic = new char[nsize * nsize];
  if( (size % 2) == 0 ) {
    n = 2;
  } else {
    n = 3;
  }
  for(i = 0; i < size/n; i++) {
    for(j = 0; j < size/n; j++) {
      old = box(n, i, j);
      trns = t->transform(old);
      fill(i, j, trns);
    }
  }
  delete pic;
  pic = npic;
  size = nsize;
  npic = 0;
  nsize = 0;
}

/*
 * Private: gets a box for transform
 */
std::string Art::box(int fact, int x, int y) {
  std::string a = "";
  int i, j;
  for( i = 0 ; i < fact; i++ ) {
    for( j = 0; j < fact; j++ ) {
      a += pic[(x*fact+i)*size + y*fact+j];
    }
  }
  return a;
}

/*
 * Private function, fills a box for transform
 */
void Art::fill(int x, int y, std::string s) {
  int fact = -1;
  unsigned int i, j;
  if( s.length() == 9 ) {
    if( (nsize % 3) == 0 ) {
      fact = 3;
    } else {
      fact = -1;
    }
  } else {
    if( s.length() == 16 ) {
      if( (nsize % 4) == 0 ) {
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
      npic[(x*fact+i)*nsize + y*fact+j] = s[i*fact + j];
    }
  }
}

/*
 * Private function, determines new box size
 * for transform
 */
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
