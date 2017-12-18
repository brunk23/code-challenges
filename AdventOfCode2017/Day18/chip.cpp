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
  registers[26] = 1;
  highestInst = 0;
  instPtr = 0;
  lastSnd = 0;
}

Chip::~Chip() {
  cerr << "The chip is dead. Long live the chip." << endl;
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
    cmd += snd * OPFACT;
    arg = 0;
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
    if( command[6] >= 'a' && command[6] <= 'z' ) {
      cmd += rmul * OPFACT;
      arg = command[6] - 'a';
    } else {
      cmd += mul * OPFACT;
      arg = getint(command);
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
    dump();
    return -1;
  }

  instPtr += 2;
  return 0;
}

/*
 * Repeatedly call step until done
 */
int Chip::run() {

  return 0;
}

/*
 * Repeatedly call step watching for rcv
 */
int Chip::watch() {
  int cmd, dest;

  while( true) {
    cmd = mem(instPtr) / OPFACT;
    dest = mem(instPtr) % OPFACT;
    if( cmd == rcv && reg(dest) != 0 ) {
      cerr << "recalled " << lastSnd << endl;
      break;
    }
    if( step() == -1 ) {
      break;
    }
  }
  return 0;
}

void Chip::regs() {
  int i;
  cerr << "iPtr: " << instPtr << endl;
  cerr << "Nonzero Registers:" << endl;
  for( i = 0; i < REGNUM; i++ ) {
    if( registers[i] != 0 ) {
      cerr << i << ": " << registers[i] << ", ";
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
  return lastSnd = reg(r);
}

int Chip::iset(int r, int v) {
  return registers[r] = v;
}

int Chip::iadd(int r, int v) {
  return registers[r] += v;
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
    instPtr += 2 * v;
  } else {
    instPtr += 2;
  }
  return 0;
}

int Chip::ircv(int r) {
  if( reg(r) != 0 ) {
    cerr << "rcv " << static_cast<char>('a'+r) << " " << lastSnd << endl;
    return reg(r);
  }
  return 0;
}

int Chip::reg(int addr) {
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
