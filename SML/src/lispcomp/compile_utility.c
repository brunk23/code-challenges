#include "compiler.h"
#include "compile_utility.h"
#include "compile_messages.h"

/* Will return a uniq ID number each time it's called */
int getID() {
  static int ID = 0;
  ID++;
  return ID;
}

int iptr(int delta) {
  static int instructionPointer = 0;
  int temp;
  
  /* Return value before modification */
  temp = instructionPointer;
  instructionPointer += delta;
    
  if( instructionPointer < 0 ) {
    emessg("Memory underun",1);
  }
  if( instructionPointer >= MEMSIZE ) {
    emessg("Memory overrun",1);
  }
  
  return temp;
}
