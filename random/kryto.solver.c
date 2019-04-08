#include <stdio.h>
#include <stdlib.h>

/*
 * This is readnum.s in synacor machine
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
  int val = a[0], j;
  for( j = 0; j < 4; j++ ) {
    switch( ops[j] ) {
    case 0:
      val += a[j+1];
      break;
    case 1:
      val *= a[j+1];
      break;
    case 2:
      if( val > a[j+1] ) {
	val -= a[j+1];
      } else {
	return -1;
      }
      break;
    case 3:
      if( (val % a[j+1]) == 0 ) {
	val /= a[j+1];
      } else {
	return -1;
      }
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
  int i;
  for( i = 0; i < 4; i++ ) {
    printf("%i %c ",a[i], oper[ ops[i] ]);
  }
  printf("%i\n",a[i]);
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
	    return 1;
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
 */
int find_solution(int *a, int goal) {
  int i = 0, c[5], tmp;

  /* Zero out the stack encoding */
  for( i = 0; i < 5; i++ ) {
    c[i] = 0;
  }

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

int main() {
  int nums[5], goal;
  char solution[17];

  for( goal = 0; goal < 17; goal++ ) {
    solution[goal] = 0;
  }
  
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
