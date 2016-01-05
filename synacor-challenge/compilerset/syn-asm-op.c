#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "synacor_a.h"

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
      return len;
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
      memory[pc++] = or;
      strind += len;
      fill(3);
      return 0;
    }
    if( len == 3 && inbuffer[strind+1] == 'u' &&
	inbuffer[strind+2] == 't') {
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
      memory[pc++] = pop;
      strind += len;
      fill(1);
      return 0;
    }
    if( len == 4 && inbuffer[strind+1] == 'u' &&
	inbuffer[strind+2] == 's' &&
	inbuffer[strind+3] == 'h' ) {
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
      memory[pc++] = ret;
      strind += len;
      return 0;
    }
    if( len == 4 && inbuffer[strind+1] == 'm' &&
	inbuffer[strind+2] == 'e' &&
	inbuffer[strind+3] == 'm' ) {
      memory[pc++] = rmem;
      strind += len;
      fill(2);
      return 0;
    }

  case 's':
    if( len == 3 && inbuffer[strind+1] == 'e' &&
	inbuffer[strind+2] == 't') {
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

  return len;
}

int inv_op() {
  fprintf(stderr,"Unrecognized opcode:\n%s",inbuffer);
  return 0;
}

/*
 * This will fill 'words' with the content on the line
 * leaves index after the last byte of the last word info.
 */
int fill( int words ) {

  return 0;
}