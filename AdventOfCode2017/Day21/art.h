#ifndef ART_H
#define ART_H

#include <iostream>
#include <string>
#include "tlist.h"

class Art {
 private:
  const unsigned int size;
  char *pic;
  TList *t;

 public:
  Art(int, TList *);
  ~Art();

  int pixels();
  void fill(std::string);
  void fill(int, int, std::string);
  unsigned int nextsize();
  std::string box2(int,int);
  std::string box3(int,int);

  friend std::ostream& operator<<(std::ostream&, const Art&);
};

#endif
