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
  highestInst = 0;
  instPtr = 0;
  lastSnd = 0;
}

/*
 * Will add a command to the chip memory.
 */
int Chip::add(string command) {
  switch( command[1] ) {
  case 'n':   // snd
    
    break;
  case 'e':   // set
    
    break;
  case 'd':   // add
    
    break;
  case 'u':   // mul
    
    break;
  case 'o':   // mod
    
    break;
  case 'c':   // rcv
    
    break;
  case 'g':   // jgz

    break;
  default:
    cerr << "Unknown command: " << command << endl;
    return -1;
    break;
  }

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
