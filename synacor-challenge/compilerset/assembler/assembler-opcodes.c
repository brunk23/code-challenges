#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

/*
 * This consumes the string passed to it and
 * all arguments after it.
 */
int opcode(int len) {
  switch( inbuffer[strind] ) {
  case 'a':
    if( len == 3 && inbuffer[strind+2] == 'd' ) {
      if( inbuffer[strind+1] == 'n' ) {
	/* AND */
	memory[pc++] = and;
	strind += len;
	fill(3);
	return 0;
      }
      if( inbuffer[strind+1] == 'd' ) {
	/* ADD */
	memory[pc++] = add;
	strind += len;
	fill(3);
	return 0;
      }
    }
    inv_op();
    break;

  case 'c':
    if( len == 4 && inbuffer[strind+1] == 'a' &&
	inbuffer[strind+2] == 'l' &&
	inbuffer[strind+3] == 'l' ) {
      /* CALL */
      memory[pc++] = call;
      strind += len;
      fill(1);
      return 0;
    }
    inv_op();
    break;

  case 'd':
    if( len == 4 && inbuffer[strind+1] == 'a' &&
	inbuffer[strind+2] == 't' &&
	inbuffer[strind+3] == 'a' ) {
      /* DATA */
      strind += len;
      process_data_line();
      return 0;
    }
    inv_op();
    break;

  case 'e':
    if( len == 2 && inbuffer[strind+1] == 'q' ) {
      /* EQ */
      memory[pc++] = eq;
      strind += len;
      fill(3);
      return 0;
    }
    inv_op();
    break;

  case 'g':
    if( len == 2 && inbuffer[strind+1] == 't' ) {
      /* GT */
      memory[pc++] = gt;
      strind += len;
      fill(3);
      return 0;
    }
    inv_op();
    break;

  case 'h':
    if( len == 4 && inbuffer[strind+1] == 'a' &&
	inbuffer[strind+2] == 'l' &&
	inbuffer[strind+3] == 't' ) {
      /* HALT */
      memory[pc++] = halt;
      strind += len;
      return 0;
    }
    inv_op();
    break;

  case 'i':
    if( len == 2 && inbuffer[strind+1] == 'n' ) {
      /* IN */
      memory[pc++] = in;
      strind += len;
      fill(1);
      return 0;
    }
    inv_op();
    break;

  case 'j':
    if( len == 2 ) {
      if( inbuffer[strind+1] == 't' ) {
	/* JT */
	memory[pc++] = jt;
	strind += len;
	fill(2);
	return 0;
      }
      if( inbuffer[strind+1] == 'f' ) {
	/* JF */
	memory[pc++] = jf;
	strind += len;
	fill(2);
	return 0;
      }
    }
    if( len == 3 && inbuffer[strind+1] == 'm' &&
	inbuffer[strind+2] == 'p' ) {
      /* JMP */
      memory[pc++] = jmp;
      strind += len;
      fill(1);
      return 0;
    }
    inv_op();
    break;

  case 'm':
    if( len == 3 && inbuffer[strind+1] == 'o' &&
	inbuffer[strind+2] == 'd') {
      /* MOD */
      memory[pc++] = mod;
      strind += len;
      fill(3);
      return 0;
    }
    if( len == 4 && inbuffer[strind+1] == 'u' &&
	inbuffer[strind+2] == 'l' &&
	inbuffer[strind+3] == 't') {
      /* MULT */
      memory[pc++] = mult;
      strind += len;
      fill(3);
      return 0;
    }
    inv_op();
    break;

  case 'n':
    if( len == 3 && inbuffer[strind+1] =='o') {
      if( inbuffer[strind+2] == 'p' ) {
	/* NOP */
	memory[pc++] = nop;
	strind += len;
	return 0;
      }
      if( inbuffer[strind+2] == 't' ) {
	/* NOT */
	memory[pc++] = not;
	strind += len;
	fill(2);
	return 0;
      }
    }
    inv_op();
    break;

  case 'o':
    if( len == 2 && inbuffer[strind+1] == 'r' ) {
      /* OR */
      memory[pc++] = or;
      strind += len;
      fill(3);
      return 0;
    }
    if( len == 3 && inbuffer[strind+1] == 'u' &&
	inbuffer[strind+2] == 't') {
      /* OUT */
      memory[pc++] = out;
      strind += len;
      fill(1);
      return 0;
    }
    inv_op();
    break;

  case 'p':
    if( len == 3 && inbuffer[strind+1] == 'o' &&
	inbuffer[strind+2] == 'p') {
      /* POP */
      memory[pc++] = pop;
      strind += len;
      fill(1);
      return 0;
    }
    if( len == 4 && inbuffer[strind+1] == 'u' &&
	inbuffer[strind+2] == 's' &&
	inbuffer[strind+3] == 'h' ) {
      /* PUSH */
      memory[pc++] = push;
      strind += len;
      fill(1);
      return 0;
    }
    inv_op();
    break;

  case 'r':
    if( len == 3 && inbuffer[strind+1] == 'e' &&
	inbuffer[strind+2] == 't' ) {
      /* RET */
      memory[pc++] = ret;
      strind += len;
      return 0;
    }
    if( len == 4 && inbuffer[strind+1] == 'm' &&
	inbuffer[strind+2] == 'e' &&
	inbuffer[strind+3] == 'm' ) {
      /* RMEM */
      memory[pc++] = rmem;
      strind += len;
      fill(2);
      return 0;
    }

  case 's':
    if( len == 3 && inbuffer[strind+1] == 'e' &&
	inbuffer[strind+2] == 't') {
      /* SET */
      memory[pc++] = set;
      strind += len;
      fill(2);
      return 0;
    }
    inv_op();
    break;

  case 'w':
    if( len == 4 && inbuffer[strind+1] == 'm' &&
	inbuffer[strind+2] == 'e' &&
	inbuffer[strind+3] == 'm' ) {
      /* WMEM */
      memory[pc++] = wmem;
      strind += len;
      fill(2);
      return 0;
    }
    inv_op();
    break;
      
  default:
    inv_op();
    break;
    
  }

  strind += len;
  return len;
}

int inv_op() {
  fprintf(stderr,"Unrecognized opcode:\n%s",inbuffer);
  return 0;
}
