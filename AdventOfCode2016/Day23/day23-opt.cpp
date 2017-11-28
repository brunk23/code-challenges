#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#define CPY 4
#define JNZ 8
#define INC 16
#define DEC 32
#define TGL 64
#define REGDEST 1
#define REGSRC 2
#define INSTSIZE 3
#define MEMSIZE INSTSIZE*50

enum regs { a, b, c, d };

void init();
void dump();
void loadState();
void dec();
void inc();
void run();
void cpy();
void jnz();
void tgl();

struct machine {
  int ip;
  int reg[4];
  int mem[MEMSIZE];
} m;

void init() {
  for(m.ip = 0 ; m.ip < 4; m.ip++) {
    m.reg[m.ip] = 0;
  }
  for(m.ip = 0 ; m.ip < MEMSIZE; m.ip++) {
    m.mem[m.ip] = 0;
  }
  m.ip = 0;
  m.reg[0] = 12;
}

void loadState() {
  string input;
  int value,i;
  bool negative;
  int address = 0;
  
  while( cin >> input ) {
    switch( input[0] ) {

    case 't':
      m.mem[address] = TGL;
      cin >> input;
      m.mem[address+1] = 0xe8;
      if( (input[0] >='a') && (input[0] <='d') ) {
	m.mem[address] += REGDEST;
	m.mem[address+2] = input[0] - 'a';
      } else {
	value = 0;
	negative = false;
	for(i = 0; i < input.length(); i++) {
	  if( input[i] == '-' ) {
	    negative = true;
	    continue;
	  }
	  value *= 10;
	  value += input[i] -'0';
	}
	if( negative ) {
	  value *= -1;
	}
	m.mem[address+2] = value;
      }
      break;
      
    case 'c':
      m.mem[address] = CPY;
      cin >> input;
      if( (input[0] >='a') && (input[0] <='d') ) {
	m.mem[address] += REGSRC;
	m.mem[address+1] = input[0] - 'a';
      } else {
	value = 0;
	negative = false;
	for(i = 0; i < input.length(); i++){
	  if( input[i] == '-' ) {
	    negative = true;
	    continue;
	  }
	  value *= 10;
	  value += input[i] - '0';
	}
	if(negative) {
	  value *= -1;
	}
	m.mem[address+1] = value;
      }
      cin >> input;
      if( (input[0] >='a') && (input[0] <='d') ) {
	m.mem[address] += REGDEST;
	m.mem[address+2] = input[0] - 'a';
      } else {
	value = 0;
	negative = false;
	for(i = 0; i < input.length(); i++){
	  if( input[i] = '-' ) {
	    negative = true;
	    continue;
	  }
	  value *= 10;
	  value += input[i] - '0';
	}
	if(negative) {
	  value *= -1;
	}
	m.mem[address+2] = value;
      }
      break;

    case 'j':
      m.mem[address] = JNZ;
      cin >> input;
      if( (input[0] >= 'a') && (input[0] <= 'd') ) {
	m.mem[address] += REGSRC;
	m.mem[address+1] = input[0] - 'a';
      } else {
	value = 0;
	negative = false;
	for(i = 0; i < input.length(); i++) {
	  if( input[i] == '-' ) {
	    negative = true;
	    continue;
	  }
	  value *= 10;
	  value += input[i] -'0';
	}
	if( negative ) {
	  value *= -1;
	}
	m.mem[address+1] = value;
      }
      cin >> input;
      if( (input[0] >= 'a') && (input[0] <= 'd') ) {
	m.mem[address] += REGDEST;
	m.mem[address+2] = input[0] - 'a';
      } else {
	value = 0;
	negative = false;
	for(i = 0; i < input.length(); i++) {
	  if( input[i] == '-' ) {
	    negative = true;
	    continue;
	  }
	  value *= 10;
	  value += input[i] -'0';
	}
	if( negative ) {
	  value *= -1;
	}
	m.mem[address+2] = value;
      }
      break;

    case 'i':
      cin >> input;
      m.mem[address] = INC + REGDEST;
      m.mem[address+1] = 0xf0;
      m.mem[address+2] = input[0] - 'a';
      break;
      
    case 'd':
      cin >> input;
      m.mem[address] = DEC + REGDEST;
      m.mem[address+1] = 0xff;
      m.mem[address+2] = input[0] -'a';
      break;
      
    default:
      cerr << "Malformed input file." << endl;
      cerr << input << endl;
      dump();
      return;
    }
    address += INSTSIZE;
  }
}

void dump() {
  int i;

  cout << "ip: " << m.ip << endl;
  cout << "Regs: [" << m.reg[0] << "," << m.reg[1] << ","
       << m.reg[2] << "," << m.reg[3] << "]" << endl;
  for(i = 0; i < MEMSIZE; i++) {
    if( (i%15) == 0) {
      cout << "\n" << i/3 << ": ";
    } else {
      if( (i%3)==0 ) {
	cout << "|";
      }
    }
    cout << m.mem[i] << "\t";
  }
  cout << endl;
}

// This only has one argument it is in dest, it should
// always be a register.
void dec() {
  if( m.mem[m.ip] & REGDEST ) {
    m.reg[ m.mem[m.ip+2] ]--;
  } else {
    return;			// do not decrement values
  }
}

void inc() {
  if( m.mem[m.ip] & REGDEST ) {
    m.reg[ m.mem[m.ip+2] ]++;
  } else {
    return;			// do not decrement values
  }
}

// It seems like the destination should always be a direct
// but handle the register case anyway
void jnz() {
  int offset;
  if( (m.mem[m.ip] & REGSRC) ) {
    if( m.reg[ m.mem[m.ip+1] ] == 0 ) {
      m.ip += INSTSIZE;
      return;
    }
  } else {
    if( m.mem[ m.ip+1 ] == 0 ) {
      m.ip += INSTSIZE;
      return;
    }
  }
  if( m.mem[m.ip] & REGDEST ) {
    offset = m.reg[ m.mem[m.ip+2] ];
  } else {
    offset = m.mem[ m.ip+2 ];
  }
  offset *= INSTSIZE;
  m.ip += offset;
}

// The destination should always be a register, but handle
// this anyway
void cpy() {
  int data;
  if( (m.mem[m.ip] & REGSRC) ) {
    data = m.reg[ m.mem[m.ip+1] ];
  } else {
    data = m.mem[ m.ip+1 ];
  }
  if( (m.mem[m.ip] & REGDEST) ) {
    m.reg[ m.mem[m.ip+2] ] = data;
  } else {
    return;			// Ignore attempt to cpy to number
  }
}

void tgl() {
  int a, dest, flags;
  if( (m.mem[m.ip] & REGDEST) ) {
    dest = m.reg[ m.mem[m.ip+2] ];
  } else {
    dest = m.mem[ m.ip+2 ];
  }
  dest *= INSTSIZE;
  a = m.mem[ m.ip + dest ];
  flags = a & (REGDEST + REGSRC);
  if( a & JNZ ) {
    m.mem[ m.ip + dest ] = CPY + flags;
    return;
  }
  if( a & CPY ) {
    m.mem[ m.ip + dest ] = JNZ + flags;
    return;
  }
  if( a & INC ) {
    m.mem[ m.ip + dest ] = DEC + flags;
    return;
  }
  m.mem[ m.ip + dest ] = INC + flags;
}

void run() {
  string tmp;
  int n;
  while( (m.mem[ m.ip ]) != 0 ) {
    n = m.mem[ m.ip ] & (CPY + JNZ + DEC + INC + TGL);
    switch( n ) {
    case CPY:
      cpy();
      m.ip += INSTSIZE;
      break;
    case DEC:
      dec();
      m.ip += INSTSIZE;
      break;
    case INC:
      inc();
      m.ip += INSTSIZE;
      break;
    case JNZ:
      jnz();
      break;
    case TGL:
      tgl();
      m.ip += INSTSIZE;
      break;
    default:
      break;
    }
    // dump();
    // sleep(1);
  }
}

int main(int argc, char *argv[]) {
  init();

  loadState();

  dump();

  run();

  dump();

  cout << "Reg A: " << m.reg[0] << endl;
  
  return 0;
}
