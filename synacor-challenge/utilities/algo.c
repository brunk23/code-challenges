
#include <stdio.h>
#include <stdlib.h>

#define REGMAX 32768

/* http://user.das.ufsc.br/~gb/fei/ackermann.html */

/*
 * This function behaves like Ackermann's functions with one
 * exception.  A(m,0) does not equal A(m-1,1) It is A(m-1,x)
 */

/*
 * Original: Generate whole array each time (gcc -Wall -g)
 *     1m59.41s real     1m58.47s user     0m00.18s system
 *
 * Change 1: Generate only rows 1, 2, 3 each pass. Row 0 is
 * constant. Only generate A[4][0] and A[4][1] (gcc -Wall -g)
 *     1m20.08s real     1m19.56s user     0m00.06s system
 *
 * Change 2: Compiler flags (gcc -O2)
 *     0m48.10s real     0m47.84s user     0m00.04s system
 *
 * End result: Runs on 40.3% of original time! Significant.
 */

typedef unsigned short int ushort;

ushort r0, r1, r7;

ushort A[5][REGMAX];


struct STACKOBJ {
  struct STACKOBJ *next;
  ushort value;
};

struct STACKOBJ *stack;

ushort push(a) {
  struct STACKOBJ *sptr;
  sptr = malloc(sizeof(struct STACKOBJ));
  sptr->next = stack;
  sptr->value = a;
  stack = sptr;
  printf("push r0\n");
  return 0;
}

ushort pop() {
  struct STACKOBJ *sptr;
  ushort v;
  sptr = stack;
  v = sptr->value;
  stack = sptr->next;
  free(sptr);
  printf("pop r0\n");
  return v;
}

ushort algo() {
  if( r0 == 0 ) {
    r0 = r1 + 1;
    return 0;
  }
  if( r1 == 0 ) {
    r0--;
    r1 = r7;
    algo();
    return 0;
  }
  push(r0);
  r1--;
  algo();
  r1 = r0;
  r0 = pop();
  r0--;
  algo();
  return 0;
}


int buildarray() {
  ushort b;
  int x;

  A[1][0] = A[0][r7];
  for( x = 1; x < REGMAX; ++x) {
    b = A[1][x-1];
    A[1][x] = A[0][b];
  }
  A[2][0] = A[1][r7];
  for( x = 1; x < REGMAX; ++x) {
    b = A[2][x-1];
    A[2][x] = A[1][b];
  }
  A[3][0] = A[2][r7];
  for( x = 1; x < REGMAX; ++x) {
    b = A[3][x-1];
    A[3][x] = A[2][b];
  }
  A[4][0] = A[3][r7];
  b = A[4][0];
  A[4][1] = A[3][b];
  return 0;
}
  

int main() {
  int x;
  
  r0 = 4;
  r1 = 1;
  r7 = 0;
 
  for( x = 0; x < REGMAX; ++x) {
    A[0][x] = (x+1)%REGMAX;
  }
  
  for( r7 = 0; r7 < REGMAX; ++r7 ) {
    buildarray();
    if( A[r0][r1] == 6 ) {
      printf("Found a hit! %i\n",r7);
    }
  }
  
  return 0;
}

/* 25734  -- There was one hit */
