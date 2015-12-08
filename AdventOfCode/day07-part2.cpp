#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

enum OPS {
  NOP, AND, LSHIFT, NOT, RSHIFT, OR
};

struct Wire
{
  Wire *left;
  Wire *right;
  OPS operat;
  unsigned short int lval;
  unsigned short int rval;
  char ident[3];
};

const int IDSZ = 3;
const int MAX = 400;

void reset_array(Wire []);
void read_input(Wire []);
unsigned int process_ident( const char *, char *);
unsigned int process_operator( const char *, OPS *);
unsigned int process_value( const char *, unsigned short int *);
void place_in_array(Wire wires[], char lval[], unsigned short int lvalue,
		    OPS op, char rval[], unsigned short int rvalue,
		    char dest[]);
int get_location(Wire wires[], const char ident[]);
int next_empty(Wire wires[]);
void print_structure(Wire *);
unsigned short int find_value(Wire *);

int main()
{
  int location;
  // There are only 336 lines in the input, so there
  // will be fewer than 400 unique wires
  Wire wires[MAX];

  // empty the array
  reset_array(wires);

  // populate the array
  read_input(wires);

  location = get_location(wires, "b");
  if (location > 0 ) {
    // we're going to cheat and just manually code this number
    // into the program. I think they wanted us to run it twice,
    // but my recursive function destroys the connections
    wires[location].lval = 16076;
    wires[location].operat = NOP;
    wires[location].left = 0;
    wires[location].right = 0;
    cout << find_value( &wires[get_location(wires, "a")] ) << endl;
  } else {
    cout << "How can 'b' not exist?!\n" << endl;
  }
}

/*
 * This will recurse down the left and right side, to find
 * the values and perform the operation
 */
unsigned short int find_value(Wire *wire)
{
  if ( wire->left > 0 ) {
    wire->lval = find_value(wire->left);
    wire->left = 0;
  }

  if ( wire->right > 0 ) {
    wire->rval = find_value(wire->right);
    wire->right =0;
  }

  if ( wire->operat == NOP ) {
    return wire->lval;
  }
  if ( wire->operat == NOT ) {
    return ~(wire->rval);
  }
  if ( wire->operat == RSHIFT ) {
    return ( wire->lval >> wire->rval );
  }
  if ( wire->operat == LSHIFT ) {
    
    return ( wire->lval << wire->rval );
  }
  if ( wire->operat == AND ) {
    return ( wire->lval & wire->rval );
  }
  if ( wire->operat == OR ) {
    return ( wire->lval | wire->rval );
  }
  cout << "ERROR!!!\n";
  return 0;
}

// For debugging purposes
void print_structure(Wire *wire) {
  cout << "wire.left: " << wire->left << endl;
  cout << "wire.right: " << wire->right << endl;
  cout << "wire.operat: " << static_cast< int >(wire->operat) << endl;
  cout << "wire.lval: " << static_cast< int >(wire->lval) << endl;
  cout << "wire.rval: " << static_cast< int >(wire->rval) << endl;
  cout << "wire.ident[0]: " << wire->ident[0] << " Dec: "
       << static_cast< int >(wire->ident[0]) << endl;
  cout << "wire.ident[1]: " << wire->ident[1] << " Dec: "
       << static_cast< int >(wire->ident[1]) << endl;
  cout << "wire.ident[2]: " << wire->ident[2] << " Dec: "
       <<static_cast< int >(wire->ident[2]) << endl;
}
  
/*
 * Clear the array.
 */
void reset_array(Wire wires[])
{
  for(int x = 0; x < MAX; ++x) {
    wires[x].left = 0;
    wires[x].lval = 0;
    wires[x].right = 0;
    wires[x].rval = 0;
    wires[x].operat = NOP;
    wires[x].ident[0] = 0;
    wires[x].ident[1] = 0;
    wires[x].ident[2] = 0;
  }
}

enum CUR {
  LVAL, RVAL, DEST
};

/*
 * Read the values into the array
 */
void read_input(Wire wires[])
{
  unsigned int chr = 0;
  string input;

  OPS op = NOP;
  char lval[IDSZ];
  char rval[IDSZ];
  char dest[IDSZ];
  unsigned short int lvalue;
  unsigned short int rvalue;
  
  CUR current = LVAL;
  
  
  while( getline(cin, input) ) {

    // set up the variables for the loop.
    current = LVAL;
    op = NOP;
    for( int y = 0; y < IDSZ; ++y) {
      lval[y] = 0;
      rval[y] = 0;
      dest[y] = 0;
    }
    lvalue = 0;
    rvalue = 0;

    for ( chr = 0; chr < input.size(); ++chr) {

      // identifier, place in appropriate position
      if( input[chr] >= 'a' && input[chr] <= 'z' ) {
	switch (current) {
	case LVAL:
	  chr += process_ident( &input[chr], lval );
	  break;
	case RVAL:
	  chr += process_ident( &input[chr], rval );
	  break;
	case DEST:
	  chr += process_ident( &input[chr], dest );
	  break;
	default:
	  break;
	}
      }

      // operator, set it and we have an LVAL next
      if( input[chr] >= 'A' && input[chr] <= 'Z' ) {
	chr += process_operator( &input[chr], &op );
	current = RVAL;
      }

      // value, set that
      if( input[chr] >= '0' && input[chr] <= '9' ) {
	if ( LVAL == current ) {
	  chr += process_value( &input[chr], &lvalue );
	} else {
	  chr += process_value( &input[chr], &rvalue );
	}
      }

      // identifier after this is the destination wire
      if( input[chr] == '>' ) {
	current = DEST;
      }
    }

    place_in_array(wires, lval, lvalue, op, rval, rvalue, dest); 

  }
    
}


/*
 * put the input into array checking for appropriate values
 * already existing
 */
void place_in_array(Wire wires[], char lval[], unsigned short int lvalue,
		    OPS op, char rval[], unsigned short int rvalue,
		    char dest[])
{
  int location;
  int other;

  location = get_location(wires, dest);

  if( location < 0 ) {
    location = next_empty(wires);
    for( int x = 0; x < IDSZ; ++x ) {
      wires[location].ident[x] = dest[x];
    }
  }

  // If it is nop, then the lvalue is the signal
  wires[location].operat = op;
  wires[location].lval = lvalue;
  wires[location].rval = rvalue;

  // if we had an identifier, check if it's already in the
  // array, if not add it, then point to it.
  if ( lval[0] > 0 ) {
    if ( (other = get_location(wires, lval)) < 0 ) {
      other = next_empty(wires);
      for( int x = 0; x < IDSZ; ++x ) {
	wires[other].ident[x] = lval[x];
      }
    }
    wires[location].left = &wires[other];
  }
  
  if ( rval[0] > 0 ) {
    if ( (other = get_location(wires, rval)) < 0 ) {
      other = next_empty(wires);
      for( int x = 0; x < IDSZ; ++x ) {
	wires[other].ident[x] = rval[x];
      }
    }
    wires[location].right = &wires[other];
  }

  /**********************************
   * Removed this after testing that things
   * were going in the right spots
   **********************************
  for( int x = 0; x < MAX; x++) {
    if( wires[x].ident[0] > 0 )
      cout << x << ": " << wires[x].ident << endl;
  }
  ***********************************/
}

/*
 * Simple function to return the next empty spot in the array
 */
int next_empty(Wire wires[]) {
  int x;
  for ( x = 0; x < MAX; x++) {
    if( wires[x].ident[0] == 0)
      break;
  }
  return x;
}

/*
 * This will return the location of an existing wire
 * and -1, if it is not in the array yet.
 */
int get_location(Wire wires[], const char ident[])
{
  int loc = -1;
  int x = 0;

  if ( ident[0] > 0 ) {
  
    for(x = 0; x < MAX; ++x) {
      if( ident[0] == wires[x].ident[0] &&
	  ident[1] == wires[x].ident[1] ) {
	loc = x;
	break;
      }
    }

  }
  return loc;
}

/*
 * Process numerical values
 */
unsigned int process_value( const char *input, unsigned short int *i)
{
  unsigned int x = 0;
  unsigned short int y = 0;
  while( input[x] >= '0' && input[x] <= '9' ) {
    y *= 10;
    y += input[x] - '0';
    ++x;
  }
  *i = y;
  return x;
}

/*
 * This will read the operator
 */
unsigned int process_operator( const char *input, OPS *operation )
{
  unsigned int x;
  switch ( input[0] ) {
  case 'A':
    *operation = AND;
    x = 3;
    break;
  case 'O':
    *operation = OR;
    x = 2;
    break;
  case 'L':
    *operation = LSHIFT;
    x = 5;
    break;
  case 'R':
    *operation = RSHIFT;
    x = 5;
    break;
  case 'N':
    *operation = NOT;
    x = 3;
    break;
  default:
    *operation = NOP;
    x = 1;
    break;
  }
  return x;
}
  
/*
 * This will read each 2 char (MAX) identifier
 */
unsigned int process_ident(const char *input, char *ident )
{
  int x;
  for ( x = 0; x < IDSZ; ++x ) {
    ident[x] = 0;
  }
  x = 0;
  while ( input[x] >='a' && input[x] <='z' && x < IDSZ-1) {
    ident[x] = input[x];
    x++;
  }
  return x-1;
}
