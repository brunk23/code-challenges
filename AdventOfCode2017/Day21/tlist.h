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

  bool isMatch(std::string, std::string);
  bool cmpA(char [3][3], char [3][3], int);
  void flipA(char [3][3], char [3][3], int);
  void rotA(char [3][3], char [3][3], int);
  void cpA(char [3][3], char[3][3], int);
  void printA(char [3][3], int);

 public:
  TList();
  ~TList();

  void add(std::string);
  std::string transform(std::string);

};

#endif
