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
  
  return 0;
}

void Chip::dump() {
  int i;
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
    instPtr += v;
  }
  return 0;
}

int Chip::ircv(int r) {
  if( registers[r] != 0 ) {
    cerr << "rcv " << static_cast<char>('a'+r) << " " << lastSnd << endl;
    return lastSnd;
  }
  return 0;
}

int Chip::reg(int addr) {
  return registers[ mem(addr) ];
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
