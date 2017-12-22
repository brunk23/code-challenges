#ifndef ART_H
#define ART_H

#include <iostream>
#include <string>
#include "tlist.h"

class Art {
 private:
  unsigned int size;
  unsigned int nsize;
  char *pic;
  char *npic;
  TList *t;

  void fill(int, int, std::string);
  unsigned int nextsize();
  std::string box(int,int,int);

 public:
  Art(int, TList *);
  ~Art();
  void transform();
  int pixels();
  void fill(std::string);

  friend std::ostream& operator<<(std::ostream&, const Art&);
};

#endif
