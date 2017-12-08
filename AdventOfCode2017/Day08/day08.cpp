#include <iostream>
#include <string>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::getline;
using std::string;

/*
 * I am all about the linked lists this year.
 */
struct Register {
  string name;
  int value;
  struct Register *next;
};

bool strequal(string, string);
Register *locateRegister( Register *, string);
int stringToOperator(string);
bool isValid(Register *, int, int);
Register *highestRegister(Register *);

Register *highestRegister(Register *head) {
  Register *curr = head, *highest = 0;
  int max = 0;

  while( curr ) {
    if( curr->value > max ) {
      max = curr->value;
      highest = curr;
    }
    curr = curr->next;
  }

  return highest;
}

int stringToOperator(string a) {
  if( strequal( a, "!=" ) ) {
    return 0;
  }
  if( strequal( a, "==" ) ) {
    return 1;
  }
  if( strequal( a, "<" ) ) {
    return 2;
  }
  if( strequal( a, "<=" ) ) {
    return 3;
  }
  if( strequal( a, ">" ) ) {
    return 4;
  }
  return 5;
}

bool isValid(Register *r, int op, int value) {
  switch( op ) {
  case 0:
    if( r->value != value ) {
      return true;
    }
    break;
  case 1:
    if( r->value == value ) {
      return true;
    }
    break;
  case 2:
    if( r->value < value ) {
      return true;
    }
    break;
  case 3:
    if( r->value <= value ) {
      return true;
    }
    break;
  case 4:
    if( r->value > value ) {
      return true;
    }
    break;
  case 5:
    if( r->value >= value ) {
      return true;
    }
    break;
  default:
    break;
  }
  return false;
}

bool strequal( string a, string b ) {
  unsigned int i;
  if( a.length() != b.length() ) {
    return false;
  }
  for( i = 0; i < a.length(); i++) {
    if( a[i] != b[i] ) {
      return false;
    }
  }
  return true;
}

/*
 * This will return a pointer to the register object
 * If it does not exist, adds it to the list and sets
 * it to zero.
 */
Register *locateRegister( Register *head, string desc ) {
  Register *curr, *notfound = 0;
  curr = head;

  while( curr ) {
    if( strequal( curr->name, desc ) ) {
      return curr;
    }
    notfound = curr;
    curr = curr->next;
  }
 
  curr = notfound;

  notfound = new Register;
  notfound->next = 0;
  notfound->value = 0;
  notfound->name = desc;
  if( curr ) {
    curr->next = notfound;
  }

  return notfound;
}

/*
 * Input structure
 * LINE | REG {inc,dec} VALUE "if" REG {==,!=,<,<=,>,>=} VALUE
 */

int main() {
  string input;
  Register *head = 0, *curr, *other;
  bool incrementp;
  int incdec, comp, op, max = 0;

  // This reads the first register
  while( cin >> input ) {
    curr = locateRegister(head, input);
    if( 0 == head ) {
      head = curr;
    }
    
    if( !(cin >> input) ) {
      cerr << "EOF at {inc,dec}" << endl;
      return 1;
    }
    if( strequal( input, "inc" ) ) {
      incrementp = true;
    } else {
      incrementp = false;
    }

    if( !(cin >> incdec) ) {
      cerr << "INVALID incdec value" << endl;
      return 1;
    }

    if( !(cin >> input) ) {
      cerr << "Expected conditional statement" << endl;
      return 1;
    }

    if( !(cin >> input) ) {
      cerr << "No second register!" << endl;
      return 1;
    }
    other = locateRegister(head, input);

    if( !(cin >> input) ) {
      cerr << "No conditional" << endl;
      return 1;
    }
    op = stringToOperator(input);


    if( !(cin >> comp) ) {
      cerr << "No Comparison Value" << endl;
      return 1;
    }

    if( isValid( other, op, comp) ) {
      if( !incrementp ) {
	incdec *= -1;
      }
      curr->value += incdec;
      if( curr->value > max ) {
	max = curr->value;
      }
    }

  }  // End while loop

  curr = highestRegister(head);
  cout << "The highest register had a value of " << curr->value
       << endl;
  cout << "The highest value of all time was " << max << endl;

  return 0;
}
