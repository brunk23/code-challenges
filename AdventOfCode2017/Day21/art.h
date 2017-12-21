#ifndef ART_H
#define ART_H

#include <iostream>
#include <string>

class Art {
 private:
  const unsigned int size;
  char *pic;

 public:
  Art(int);
  ~Art();

  int pixels();
  void fill(std::string);
  std::string box2(int,int);
  std::string box3(int,int);

  friend std::ostream& operator<<(std::ostream&, const Art&);
};

#endif
