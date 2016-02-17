#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * Synacor Disassmbler
 *
 * This is updated to make the output clear
 */

int prev;

int main(int argc, char *argv[]) {
  int retval = 0;
  unsigned short int oldpc, data=0;
  prev = 0;
  if( argc != 2 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }

  init_machine();
  
  if( !(retval = read_in_file(argv[1]))) {
    fprintf(stderr,"Could not read file: %s\n",argv[1]);
    return 1;
  }

  for( pc = 0; pc < retval; ) {
    if( memory[pc] > 23 ) {
      if( data == 0 ) {
	printf("%05i:\tdata\t%05i\t",pc,memory[pc]);
      } else {
	printf("%05i\t",memory[pc]);
      }
      ++data;
      ++pc;
      if( data >= 8 ) {
	printf("\n");
	data = 0;
      }
      continue;
    }

    if(data > 0 ) {
      printf("\n");
    }
    data = 0;
    
    oldpc = pc;
    if( !((prev == 19) && memory[pc]==19) ) {
      printf("%05i:\t", pc);
    }
    inst_tble[ memory[pc] ]();
    prev = memory[oldpc];
    if( !(prev == 19 && memory[pc]==19)) {
      printf("\n");
    }
  }

  printf("\n\n");
  return 0;
}

int init_machine() {
  int x;
  inst_tble[0] = op_halt;
  inst_tble[1] = op_set;
  inst_tble[2] = op_push;
  inst_tble[3] = op_pop;
  inst_tble[4] = op_eq;
  inst_tble[5] = op_gt;
  inst_tble[6] = op_jmp;
  inst_tble[7] = op_jt;
  inst_tble[8] = op_jf;
  inst_tble[9] = op_add;
  inst_tble[10] = op_mult;
  inst_tble[11] = op_mod;
  inst_tble[12] = op_and;
  inst_tble[13] = op_or;
  inst_tble[14] = op_not;
  inst_tble[15] = op_rmem;
  inst_tble[16] = op_wmem;
  inst_tble[17] = op_call;
  inst_tble[18] = op_ret;
  inst_tble[19] = op_out;
  inst_tble[20] = op_in;
  inst_tble[21] = op_nop;
  inst_tble[22] = op_dread;
  inst_tble[23] = op_dwrite;
  pc = 0;
  
  for( x = 0; x < REGOFFSET; ++x ) {
    memory[x] = 0;
  }
  
  return 0;
}

int read_in_file(const char *filename) {
  FILE *source;
  int words_read = 0;

  if( !( source = fopen(filename, "r"))) {
    fprintf(stderr,"Could not open file for reading.\n");
    return 0;
  }

  words_read = fread(memory,
		     sizeof(unsigned short int),
		     REGOFFSET,
		     source);

  if( source ) {
    fclose(source);
  }
  return words_read;
}

/*
 * Pretty print the address
 */
unsigned short int get_add(unsigned short int a) {
  switch (memory[a]) {
  case 32768:
    printf("r0");
    break;

  case 32769:
    printf("r1");
    break;

  case 32770:
    printf("r2");
    break;

  case 32771:
    printf("r3");
    break;

  case 32772:
    printf("r4");
    break;

  case 32773:
    printf("r5");
    break;

  case 32774:
    printf("r6");
    break;

  case 32775:
    printf("r7");
    break;

  default:
    printf("%i",memory[a]);
    break;
  }
  return 0;
}

/* Just return 1 to end the program */
int op_halt() {
  printf("halt");
  pc +=1;
  return 0;
}

/* set a b :: set register a to value of b */
int op_set() {
  get_add(pc+1);
  printf(" = ");
  get_add(pc+2);
  pc += 3;
  return 0;
}

int op_push() {
  printf("push ");
  get_add(pc + 1);
  pc += 2;
  return 0;
}

int op_pop() {
  printf("pop ");
  get_add(pc + 1);
  pc += 2;
  return 0;
}

int op_eq() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" == ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_gt() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" > ");
  get_add(pc + 3);
  printf(" )");
  pc += 4; 
  return 0;
}

/* jmp a :: jump to a */
int op_jmp() {
  printf("goto ");
  get_add(pc + 1);
  pc += 2;
  return 0;
}

/* jt a b :: if a is non-zero, jump to b */
int op_jt() {
  printf("if ( ");
  get_add(pc + 1);
  printf(" ) goto ");
  get_add(pc + 2);
  pc += 3;
  return 0;
}

/* jf a b :: if a is zero, jump to b */
int op_jf() {
  printf("if !( ");
  get_add(pc + 1);
  printf(" ) goto ");
  get_add(pc + 2);
  pc += 3;
  return 0;
}

int op_add() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" + ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_mult() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" * ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_mod() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" %% ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_and() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" & ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_or() {
  get_add(pc + 1);
  printf(" = ( ");
  get_add(pc + 2);
  printf(" | ");
  get_add(pc + 3);
  printf(" )");
  pc += 4;
  return 0;
}

int op_not() {
  get_add(pc + 1);
  printf(" = ~( ");
  get_add(pc + 2);
  printf(" )");
  pc += 3;
  return 0;
}

int op_rmem() {
  get_add(pc + 1);
  printf(" = [ ");
  get_add(pc + 2);
  printf(" ]");
  pc += 3;
  return 0;
}

int op_wmem() {
  printf("[ ");
  get_add(pc + 1);
  printf(" ] = ");
  get_add(pc + 2);
  pc += 3;
  return 0;
}

int op_call() {
  printf("call ");
  get_add(pc + 1);
  pc += 2;
  return 0;
}

int op_ret() {
  printf("ret");
  pc++;
  return 0;
}

/* out <a> :: print ascii value of a to screen */
int op_out() {
  if( !(prev == 19)) {
    printf("print %c", memory[pc+1]);
  } else {
    printf("%c", memory[pc+1]);
  }
  pc += 2;
  return 0;
}

int op_in() {
  get_add(pc + 1);
  printf(" = getch();");
  pc += 2;
  return 0;
}

/* Just increment the program counter and return */
int op_nop() {
  printf("nop");
  ++pc;
  return 0;
}

/* Very Wordy Output, but conforms to the destination
 * on the left style of the rest of the lines */
int op_dread() {
  printf("[");
  get_add( pc + 1 );
  printf("]+");
  get_add( pc + 5 );
  printf(" words <-- Read Dev{");
  get_add( pc + 2 );
  printf("} ");
  get_add( pc + 3 );
  printf(":");
  get_add( pc + 4 );
  pc += 6;
  return 0;
}

int op_dwrite() {
  printf("Write Dev{");
  get_add( pc + 1 );
  printf("} ");
  get_add( pc + 2 );
  printf(":");
  get_add( pc + 3 );
  printf(" <-- [");
  get_add( pc + 4 );
  printf("]+");
  get_add( pc + 5 );
  printf(" words");
  pc += 6;
  return 0;
}
