#include <stdio.h>
#include <stdlib.h>

/*
 * This is readnum.s in synacor machine
 *
 * Implemented in synacor asm
 */
int getval() {
  char input[80];
  int val = 0;

  if( !(fgets(input,80,stdin)) ) {
    exit(1);
  }
  val = atoi(input);
  return val;
}

/*
 * Will determine the value of the current operations.
 * Returns -1 when an operation is invalid.
 */
int value(int *a, int *ops) {
  int val = a[0], j, first = 1;
  for( j = 0; j < 4; j++ ) {
    switch( ops[j] ) {
    case 0:
      val += a[j+1];
      first = 0;
      break;
    case 1:
      val *= a[j+1];
      first = 0;
      break;
    case 2:
      if( val > a[j+1] ) {
	val -= a[j+1];
      } else {
	if( first ) {
	  return -1;
	}
	val = a[j+1] - val;
      }
      first = 0;
      break;
    case 3:
      if( (val % a[j+1]) == 0 ) {
	val /= a[j+1];
      } else {
	if( (a[j + 1] % val) == 0 ) {
	  val = a[j + 1] / val;
	} else {
	  return -1;
	}
      }
      first = 0;
      break;
    default:
      return -1;
    }
  }
  return val;
}

/*
 * We found a win, print it nicely.
 */
void print_win(int *a, int *ops) {
  char oper[4] = { '+', '*', '-', '/' };
  int i, val = a[0];
  for( i = 0; i < 4; i++ ) {
    switch( oper[ ops[i] ] ) {
    case '+':
      printf("(%i%c%i)",val, oper[ ops[i] ], a[i+1]);
      val += a[i+1];
      break;
    case '*':
      printf("(%i%c%i)",val, oper[ ops[i] ], a[i+1]);
      val *= a[i+1];
      break;
    case '-':
      if( val > a[i+1] ) {
	printf("(%i%c%i)",val, oper[ ops[i] ], a[i+1]);
	val -= a[i+1];
      } else {
	printf("(%i%c%i)",a[i+1], oper[ ops[i] ], val);
	val = a[i+1] - val;
      }
      break;
    case '/':
      if( val > a[i+1] ) {
	printf("(%i%c%i)",val, oper[ ops[i] ], a[i+1]);
	val /= a[i+1];
      } else {
	printf("(%i%c%i)",a[i+1], oper[ ops[i] ], val);
	val = a[i+1] / val;
      }
      break;
    }
  }
  printf("\n");
}

/*
 * This generates all the possible operation combinations
 */
int try_all(int *a, int goal) {
  int i, j, k, m;
  int ops[4];
  
  for( i = 0; i < 4; i++) {
    ops[0] = i;
    for( j = 0; j < 4; j++) {
      ops[1] = j;
      for( k = 0; k < 4; k++) {
	ops[2] = k;
	for( m = 0; m < 4; m++ ) {
	  ops[3] = m;
	  if( goal == value(a, ops) ) {
	    print_win(a, ops);
	  }
	}
      }
    }
  }
  return 0;
}

/*
 * This is Heap's Algorithm (non-recursive) and it goes through
 * all of the variations without affecting the stack
 * requires an array equal to the amount of numbers
 *
 * Implemented in synacor asm
 */
int find_solution(int *a, int goal) {
  int i = 0, c[5], tmp;

  /* Zero out the stack encoding */
  for( i = 0; i < 5; i++ ) {
    c[i] = 0;
  }

  /* Try the initial order as well */
  try_all(a, goal);

  i = 0;
  while( i < 5 ) {
    if( c[i] < i ) {
      if( i%2 == 0 ) {
	// Swap a[0] and a[i]
	tmp = a[0];
	a[0] = a[i];
	a[i] = tmp;
      } else {
	// Swap a[c[i]] and a[i]
	tmp = a[ c[i] ];
	a[ c[i] ] = a[i];
	a[i] = tmp;
      }
      try_all(a, goal);
      c[i]++;
      i = 0;
    } else {
      c[i] = 0;
      i++;
    }
  }
  return 0;
}

/* Implemented in synacor asm */
int main() {
  int nums[5], goal;
  
  /*
   * Get the inputs
   */
  printf("a: ");  nums[0] = getval();
  printf("b: ");  nums[1] = getval();
  printf("c: ");  nums[2] = getval();
  printf("d: ");  nums[3] = getval();
  printf("e: ");  nums[4] = getval();
  printf("goal: ");  goal = getval();

  find_solution(nums, goal);
  return 0;
}
