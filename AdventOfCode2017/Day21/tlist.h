#ifndef TLIST_H
#define TLIST_H

#include <string>

class TList {
 private:

  struct transf {
    std::string orig;
    std::string chg;
    transf *next;
  };

  transf *headtwo;
  transf *tailtwo;
  transf *headthree;
  transf *tailthree;

 public:
  TList();
  ~TList();

  void add(std::string);
  std::string transform(std::string);

};

#endif
