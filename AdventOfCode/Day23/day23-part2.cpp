#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::setw;

#define MEMSIZE 100*2
#define MULT 100

enum INST {
  HLF = 1,     			// half the register
  TPL,				// triple the register
  INC,				// increment the register
  JMP,				// jump offset ( iptr += offset)
  JIE,				// jump if even
  JIO,				// jump if one
  A,
  B
};

// each instruction takes two int (first give instruction and destination
// the second is the offset

struct machine {
  // our two resisters
  long a;
  long b;

  // our instruction pointer
  int iptr;

  int mem[MEMSIZE];
};

void read_program(machine &);
void run_program(machine &);
void print_mem(machine &);

int main()
{
  machine m;
  int x = 0;

  // init the machine
  m.a = 1;
  m.b = 0;
  m.iptr = 0;
  for( x = 0; x < MEMSIZE; ++x) {
    m.mem[x] = 0;
  }
  
  read_program(m);
  run_program(m);

  cout << "The value of b is: " << m.b << endl;
  
  return 0; 
}

void read_program(machine &m)
{
  string input;
  char command[4];
  unsigned int x = 0, i = 0;
  int inst, reg, dest;
  bool valid = false;
  
  while( getline(cin, input) ) {
    inst = 0;
    reg = 0;
    dest = 0;
    valid = false;
    
    for( x = 0; x < 3; x++ ) {
      command[x] = input[x];
    }
    command[3] = 0;

    if( (strcmp(command,"hlf") == 0) ) {
      inst = HLF;
      valid = true;
    }
    if( (strcmp(command,"tpl") == 0) ) {
      inst = TPL;
      valid = true;
    }
    if( (strcmp(command,"inc") == 0) ) {
      inst = INC;
      valid = true;
    }
    if( (strcmp(command,"jmp") == 0) ) {
      inst = JMP;
      valid = true;
    }
    if( (strcmp(command,"jie") == 0) ) {
      inst = JIE;
      valid = true;
    }
    if( (strcmp(command,"jio") == 0) ) {
      inst = JIO;
      valid = true;
    }
    inst *= MULT;
    if( !valid ) {
      cout << "This isn't a valid command!" << endl;
    }
    for(; x < input.size(); ++x) {
      if( input[x] == 'a' ) {
	reg = A;
      }
      if( input[x] == 'b' ) {
	reg = B;
      }
      if( input[x] == '+' ) {
	/* positive number */
	++x;
	while( input[x] >= '0' && input[x] <= '9' ) {
	  dest *= 10;
	  dest += input[x++] - '0';
	}
      }
      if( input[x] == '-' ) {
	/* negative number */
	++x;
	while( input[x] >= '0' && input[x] <= '9' ) {
	  dest *= 10;
	  dest -= (input[x++] - '0');
	}
      }
    }
    m.mem[i++] = inst+reg;
    m.mem[i++] = dest;
  }
}

void run_program(machine &m)
{
  int inst, reg, dest, location;
  while(true) {
    //    print_mem(m);
    location = m.iptr * 2;
    inst = m.mem[location];
    dest = m.mem[location+1];
    reg = inst % MULT;
    inst /= MULT;

    switch( inst ) {
    case HLF:
      if( reg == A ) {
	m.a /= 2;
      } else {
	if ( reg == B ) {
	  m.b /= 2;
	} else {
	  cout << "ERROR, NO REGISTER" << endl;
	  return;
	}
      }
      m.iptr++;
      break;

    case TPL:
      if( reg == A ) {
	m.a *= 3;
      } else {
	if ( reg == B ) {
	  m.b *= 3;
	} else {
	  cout << "ERROR, NO REGISTER" << endl;
	  return;
	}
      }
      m.iptr++;
      break;
      
    case INC:
      if( reg == A ) {
	m.a++;
      } else {
	if ( reg == B ) {
	  m.b++;
	} else {
	  cout << "ERROR, NO REGISTER" << endl;
	  return;
	}
      }
      m.iptr++;
      break;
      
    case JMP:
      m.iptr += dest;
      break;

    case JIE:
      if( reg == A ) {
	if( (m.a % 2) == 0 ) {
	  m.iptr += dest;
	} else {
	  m.iptr++;
	}
      } else {
	if ( reg == B ) {
	  if( (m.b % 2) == 0 ) {
	    m.iptr += dest;
	  } else {
	    m.iptr++;
	  }
	} else {
	  cout << "ERROR, NO REGISTER" << endl;
	  return;
	}
      }
      break;

    case JIO:
      if( reg == A ) {
	if( m.a == 1 ) {
	  m.iptr += dest;
	} else {
	  m.iptr++;
	}
      } else {
	if ( reg == B ) {
	  if( m.b == 1 ) {
	    m.iptr += dest;
	  } else {
	    m.iptr++;
	  }
	} else {
	  cout << "ERROR, NO REGISTER" << endl;
	  return;
	}
      }
      break;

    default:
      /* End the program */
      return;
      break;
      
    }
  }
}

void print_mem(machine &m) {
  cout << "a: " << m.a << "\tb: " << m.b << "\tiptr: " << m.iptr << endl;
  for(int x = 0; x < MEMSIZE; ++x) {
    cout << setw(7) << m.mem[x];
    if( (x+1)%10 == 0 ) {
      cout << endl;
    }
  }
}
