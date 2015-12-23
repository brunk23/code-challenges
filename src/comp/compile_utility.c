/*
 * Utility functions for the compiler, they are used by other
 * functions to perform their tasks
 */

#include <stdio.h>
#include "compiler.h"
#include "compile_utility.h"

/*
 * This will allow us to use our instruction pointer more securely.
 * It ensures that it remains in bounds, it is the responsibility
 * of the program to check for -1 return value.
 */
int iptr(int delta) {
  static int instructionPointer = 0;
  int temp;
  
  /* Return value before modification */
  temp = instructionPointer;
  instructionPointer += delta;
    
  if( instructionPointer < 0 ) {
    fprintf(stderr,"ERROR: Memory underun.\n");
    return -1;
  }
  if( instructionPointer >= MEMSIZE ) {
    fprintf(stderr,"ERROR: Memory overrun.\n");
    return -1;
  }
  
  return temp;
}
