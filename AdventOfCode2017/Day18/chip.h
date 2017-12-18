#ifndef CHIP_H
#define CHIP_H

#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

#define CODESIZE 1000
#define REGNUM 26

enum commands {snd=1, set, add, radd, mul, rmul,
	       mod, rmod, rcv, jgz, rjgz};

class Chip {
 private:
  int code[CODESIZE];
  int registers[REGNUM];
  int lastSnd;
  int instPtr;
  int highestInst;

 public:
  Chip();
  int add(string);
  int step();
  int run();
  int watch();

};

#endif
