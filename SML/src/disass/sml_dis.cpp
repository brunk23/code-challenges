#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "../shared/sml_shared.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::setw;
using std::string;
using std::ifstream;
using std::setfill;

void define_codes(const char *[]);

int main(int argc, char *argv[])
{
  const char *opcodemap[MAXOP];
  int type[MEMSIZE];

  for(int x = 0; x < MEMSIZE; ++x) {
    type[x] = 0;
  }

  define_codes(opcodemap);

  int returnCode = 0, counter = 0;
  int input = 0;
  string line;
  bool indirect = false;
  char *parse, *pfull, *before;

  if( argc > 1 ) {
    ifstream filename;
    filename.open(argv[1], std::ios::in);
    if( !filename.is_open() ) {
      cout << "Unable to open file" << endl;
      return 1;
    }
    while( getline(filename, line) ) {
      parse = 0;
      pfull = new char[line.size()];
      strncpy(pfull, line.c_str(), line.size());
      parse = pfull;
      while( true ) {
	before = parse;
	input = strtol(parse, &parse, 10);
	if( parse == before || parse == 0 ) {
	  break;
	}
	cout << setw(3) << counter << ":";
	cout << setw(4) << input / OPFACT;
	cout << setw(3) << input % OPFACT;
	if( (input / OPFACT) > MAXOP ) {
	  indirect = true;
	  input -= 100 * OPFACT;
	}
	if( (input/OPFACT) < MAXOP)  {
	  cout << setw(10) << opcodemap[input/OPFACT];
	  cout << setw(4) << input % OPFACT;
	  if( indirect ) {
	    cout << " ** indirect **";
	  }
	}
	cout << endl;
	indirect = false;
	counter++;
      }
      delete pfull;
    }
  } else {
    cout << "You must enter a core file name" << endl;
  }
  return returnCode;
}

void define_codes(const char *opcodemap[]) {
  for( int x = 0; x < MAXOP; ++x ) {
    opcodemap[x] = "INV";
  }
 // These are the currently supported instructions
	
  // Arithmatic
  opcodemap[ADD]="ADD";
  opcodemap[SUBTRACT]="SUB";
  opcodemap[MULTIPLY]="MUL";
  opcodemap[DIVIDE]="DIV";
  opcodemap[MOD]="MOD";

  // memory access
  opcodemap[LOAD]="LDA";
  opcodemap[STORE]="STR";

  // i/o
  opcodemap[READ]="RD";
  opcodemap[WRITE]="WRT";
  opcodemap[SREAD]="RDS";
  opcodemap[SWRITE]="WRS";

  // flow control
  opcodemap[BRANCH]="BR";
  opcodemap[BRANCHNEG]="BRN";
  opcodemap[BRANCHZERO]="BRZ";
  opcodemap[HALT]="HLT";

  // Extended opcodes
  opcodemap[INC]="INC";
  opcodemap[DEC]="DEC";
  opcodemap[DUMP]="DMP";
  opcodemap[NOP]="NOP";

  // Stack opcodes
  opcodemap[PUSH]="PSH";
  opcodemap[POP]="POP";
  opcodemap[CALL]="CAL";
  opcodemap[RET]="RET";
}
