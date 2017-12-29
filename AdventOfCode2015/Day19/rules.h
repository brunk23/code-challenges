#ifndef RULES_H
#define RULES_H

#include <string>

class Rules {
 private:
  struct TRule {
    std::string left;
    std::string right;
    unsigned int lenL;
    unsigned int lenR;
    TRule *next;
  };

  static TRule *head;
  static TRule *tail;
  static int instances;
  TRule *curr;

 public:
  Rules();
  ~Rules();
  void reset();
  void next();
  int location(std::string a, int start);
  void add(std::string lft, std::string rgt);
  std::string replace(std::string s, int offset);

};

#endif
