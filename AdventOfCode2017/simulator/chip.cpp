#include <iostream>
#include <string>
#include "chip.h"

using std::cerr;
using std::endl;
using std::string;

/*
 * Default constructor makes an empty chip
 */
Chip::Chip() {
  int i;

  for( i = 0; i < CODESIZE; i++ ) {
    code[i] = 0;
  }

  for( i = 0; i < REGNUM; i++ ) {
    registers[i] = 0;
  }
  registers[0] = 1;
  registers[26] = 1;
  highestInst = 0;
  instPtr = 0;
  sent = 0;
  received = 0;
  messages = 0;
  head = 0;
  tail = 0;
  id = 0;
  mulcount = 0;
  stat = running;
  partner = 0;
}

Chip::Chip(Chip& other) {
  *this = other;
}

std::string Chip::regstr(int i) {
  std::string ns = "";
  ns += std::string(1,i+'a') + ": " + std::to_string(registers[i]);
  return ns;
}

std::string Chip::iptrstr() {
  std::string ns = "";
  ns += "instPtr: " + std::to_string(instPtr / WDSIZE + 1);
  return ns;
}

void Chip::halt() {
  stat = stopped;
}

Chip& Chip::operator=(Chip& other) {
  int i;

  for( i = 0; i < CODESIZE; i++ ) {
    code[i] = other.code[i];
  }

  for( i = 0; i < REGNUM; i++ ) {
    registers[i] = other.registers[i];
  }
  highestInst = other.highestInst;
  instPtr = other.instPtr;
  stat = other.stat;
  id = other.id + 1;
  registers[15] = id;

  partner = &other;

  // Chips never share message queue.
  sent = 0;
  received = 0;
  messages = 0;
  head = 0;
  tail = 0;
  return *this;
}

Chip::~Chip() {
  if( messages > 0 ) {
    while( head ) {
      tail = head->next;
      delete head;
      head = tail;
    }
  }
  dump();
  cerr << "Chip " << id << ":\tSent: " << sent
       << "\tReceived: " << received << endl;
}

void Chip::pair(Chip &other) {
  partner = &other;
}

int Chip::status() {
  return stat;
}

int Chip::numMessages() {
  return messages;
}

long Chip::nextMessage() {
  long val = head->value;
  Message *tmp = head;
  head = head->next;
  delete tmp;
  messages--;

  if( messages == 0 ) {
    head = 0;
    tail = 0;
  }
  return val;
}

/*
 * Will add a command to the chip memory.
 */
int Chip::add(string command) {
  int cmd = 0, arg = 0;
  cmd = command[4] - 'a';
  if( command[4] == '1' ) {
    cmd = 26;
  }
  switch( command[1] ) {
  case 'n':   // snd
    if( command[0] == 'j' ) {
      if( command[6] >= 'a' && command[6] <= 'z' ) {
	cmd += rjnz * OPFACT;
	arg = command[6] - 'a';
      } else {
	cmd += jnz * OPFACT;
	arg = getint(command);
      }
    } else {
      cmd += snd * OPFACT;
      arg = 0;
    }
    break;
  case 'e':   // set
    if( command[6] >= 'a' && command[6] <= 'z' ) {
      cmd += rset * OPFACT;
      arg = command[6] - 'a';
    } else {
      cmd += set * OPFACT;
      arg = getint(command);
    }
    break;
  case 'd':   // add
    if( command[6] >= 'a' && command[6] <= 'z' ) {
      cmd += radd * OPFACT;
      arg = command[6] - 'a';
    } else {
      cmd += madd * OPFACT;
      arg = getint(command);
    }
    break;
  case 'u':   // mul
    if( command[0] == 's' ) {
      if( command[6] >= 'a' && command[6] <= 'z' ) {
	cmd += rsub * OPFACT;
	arg = command[6] - 'a';
      } else {
	cmd += sub * OPFACT;
	arg = getint(command);
      }
    } else {
      if( command[6] >= 'a' && command[6] <= 'z' ) {
	cmd += rmul * OPFACT;
	arg = command[6] - 'a';
      } else {
	cmd += mul * OPFACT;
	arg = getint(command);
      }
    }
    break;
  case 'o':   // mod
    if( command[6] >= 'a' && command[6] <= 'z' ) {
      cmd += rmod * OPFACT;
      arg = command[6] - 'a';
    } else {
      cmd += mod * OPFACT;
      arg = getint(command);
    }
    break;
  case 'c':   // rcv
    cmd += rcv * OPFACT;
    arg = 0;
    break;
  case 'g':   // jgz
    if( command[6] >= 'a' && command[6] <= 'z' ) {
      cmd += rjgz * OPFACT;
      arg = command[6] - 'a';
    } else {
      cmd += jgz * OPFACT;
      arg = getint(command);
    }
    break;
  default:
    cerr << "Unknown command: " << command << endl;
    return -1;
    break;
  }
  code[highestInst] = cmd;
  highestInst++;
  code[highestInst] = arg;
  highestInst++;
  return highestInst;
}

/*
 * The actual commands will be run here
 */
int Chip::step() {
  int cmd, dest, arg;

  if( stat == stopped ) {
    return -1;
  }
  
  cmd = mem(instPtr) / OPFACT;
  dest = mem(instPtr) % OPFACT;
  arg = mem(instPtr + 1);
  
  switch( cmd ) {
  case snd:
    isnd(dest);
    break;
  case set:
    iset(dest, arg);
    break;
  case rset:
    iset(dest, reg(arg));
    break;
  case madd:
    iadd(dest, arg);
    break;
  case radd:
    iadd(dest, reg(arg));
    break;
  case mul:
    imul(dest, arg);
    break;
  case rmul:
    imul(dest, reg(arg));
    break;
  case mod:
    imod(dest, arg);
    break;
  case sub:
    isub(dest, arg);
    break;
  case rsub:
    isub(dest, reg(arg));
    break;
  case jnz:
    ijnz(dest, arg);
    return 0;
  case rjnz:
    ijnz(dest, arg);
    return 0;
  case rmod:
    imod(dest, reg(arg));
    break;
  case rcv:
    ircv(dest);
    break;
  case jgz:
    ijgz(dest, arg);
    return 0; // Do NOT break, instPtr already updates
  case rjgz:
    ijgz(dest, reg(arg));
    return 0;
  default:
    cerr << "Invalid instruction " << instPtr << endl;
    stat = stopped;
    dump();
    return -1;
  }

  instPtr += WDSIZE;
  return 0;
}

void Chip::regs() {
  int i;
  cerr << "iPtr: " << instPtr/WDSIZE+1 << endl;
  cerr << "Nonzero Registers:" << endl;
  for( i = 0; i < REGNUM; i++ ) {
    if( registers[i] != 0 ) {
      cerr << static_cast<char>(i+'a') << ": " << registers[i] << ", ";
    }
  }
  cerr << endl;
}

void Chip::dump() {
  int i;

  regs();

  for( i = 0; i < CODESIZE; i++ ) {
    cerr << code[i] << "\t";
    if( i % 10 == 9 ) {
      cerr << endl;
    }
  }
}

/********
 * BEGIN PRIVATE METHODS
 *******/

int Chip::isnd(int r) {
  Message *tmp = new Message;
  tmp->next = 0;
  tmp->value = reg(r);
  sent++;
  if( messages == 0 ) {
    head = tmp;
    tail = tmp;
  } else {
    tail->next = tmp;
    tail = tmp;
  }
  messages++;
  return messages;
}

int Chip::iset(int r, int v) {
  return registers[r] = v;
}

int Chip::iadd(int r, int v) {
  return registers[r] += v;
}

int Chip::isub(int r, int v) {
  return registers[r] -= v;
}

int Chip::imul(int r, int v) {
  return registers[r] *= v;
}

int Chip::imod(int r, int v) {
  if(v == 0 ) {
    cerr << "FATAL DIVIDE BY ZERO" <<endl;
    return -1;
  }
  return registers[r] %= v;
}

int Chip::ijgz(int r, int v) {
  if(registers[r] > 0 ) {
    instPtr += WDSIZE * v;
  } else {
    instPtr += WDSIZE;
  }
  return 0;
}

int Chip::ijnz(int r, int v) {
  if(registers[r] != 0 ) {
    instPtr += WDSIZE * v;
  } else {
    instPtr += WDSIZE;
  }
  return 0;
}

int Chip::ircv(int r) {
  if( partner->numMessages() > 0 ) {
    registers[ r ] = partner->nextMessage();
    stat = running;
    received++;
  } else {
    if( (messages == 0) && (partner->status() != running) ) {
      stat = stopped;
    } else {
      stat = waiting;
    }
    instPtr -= WDSIZE;
  }
  return 0;
}

long Chip::reg(int addr) {
  return registers[ addr ];
}

int Chip::mem(int addr) {
  return code[ addr ];
}

/*
 * Internal function to handle number arguments
 */
int Chip::getint(string command) {
  int i = 6, arg = 0;
  bool negative = false;
  if( command[i] == '-' ) {
    negative = true;
    i++;
  }
  while( command[i] >= '0' && command[i] <= '9' ) {
    arg *= 10;
    arg += command[i] - '0';
    i++;
  }
  if( negative ) {
    arg *= -1;
  }

  return arg;
}
