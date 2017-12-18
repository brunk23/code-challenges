#ifndef CHIP_H
#define CHIP_H

#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

#define CODESIZE 100
#define REGNUM 27
#define OPFACT 100

/*
 * Instructions will take 2 words.  The first word will
 * be the command opcode plus the destination register
 * a = 0, b = 1, etc.
 */
enum commands {snd=1, set, rset, madd, radd, mul, rmul,
	       mod, rmod, rcv, jgz, rjgz, running, waiting,
	       stopped};

class Chip {
 private:
  struct Message {
    long value;
    Message *next;
  };

  int code[CODESIZE];
  long registers[REGNUM];
  int lastSnd;
  int instPtr;
  int highestInst;
  int stat;
  int id;
  int sent;
  int received;
  int messages;
  Chip *partner;
  Message *head;
  Message *tail;

  int isnd(int);
  int iset(int, int);
  int iadd(int, int);
  int imul(int, int);
  int imod(int, int);
  int ijgz(int, int);
  int ircv(int);
  int reg(int);
  int mem(int);
  int getint(string);

 public:
  Chip();
  Chip(Chip&);
  ~Chip();
  int add(string);
  int step();
  int watch();
  void dump();
  void regs();
  int status();
  int numMessages();
  long nextMessage();
  void pair(Chip &);
  Chip& operator=(Chip&);
};

#endif
