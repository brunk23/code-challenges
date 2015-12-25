#ifndef SML_SHARED_H
#define SML_SHARED_H

#define MEMSIZE 1000
#define MAXOP 100
#define MAXVAL 999999
#define MINVAL -999999
#define OPFACT 1000

/*
 * Not all these opcodes were part of the original spec.
 *   Extended Opcodes Include: INC, DEC, MOD, DUMP, NOP
 *   A_opcodes are indirect opcodes. They set a flag
 *   indirect in the machine state. The memory location
 *   pointed at is loaded, high 3 digits are added to the
 *   low 3 digits and that is used as the actual memory
 *   location
 */
enum OPCODES {
  READ = 10, WRITE, SREAD, SWRITE,
  LOAD = 20, STORE,
  ADD = 30, SUBTRACT, DIVIDE, MULTIPLY, MOD,
  BRANCH = 40, BRANCHNEG, BRANCHZERO, HALT,
  INC = 60, DEC,
  PUSH = 70, POP, CALL, RET,
  A_READ = 110, A_WRITE,
  A_LOAD = 120, A_STORE,
  A_ADD = 130, A_SUBTRACT, A_DIVIDE, A_MULTIPLY, A_MOD,
  A_INC = 160, A_DEC,
  NOP = 98, DUMP
};

#endif
