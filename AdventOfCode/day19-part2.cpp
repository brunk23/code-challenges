#include <iostream>
#include <string>
#include <unistd.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

#include "day19.h"

// Read the starting elements and the start string.
Element *read_input(Element **);
Element *sort(Element *);
void generate_substrings(const Element *curr, Element *start_string,
			 Element **next);
void replace(int start, int len, const char *org, const char *repl, char *mod);
bool contains(Element *a, Element *b);
bool start_match(char *a, char *b, int index);
void print_tree(Element *a);

int main()
{
  Element *head=0, *curr=0, *gens=0, *next=0;
  Element *start_string=0, *temp=0, *temp2=0;
  Element final_string("e");
  
  head = read_input( &start_string );
  
  curr = head;

  // head and curr represent possible transformations
  // start_string and gens are the generated strings

  int x = 0;
  gens = start_string;
  temp2 = gens;
  while ( !contains( gens, &final_string)) {
    next = 0;
    while ( gens > 0 ) {
      while ( curr > 0 ) {
	generate_substrings(curr, gens, &next);
	curr = curr->getNext();
      }
      curr = head;		// reset the conversions
      gens = gens->getNext();
    }
    curr = head;
    ++x;			// didn't make it this time
    cout << "Generation: " << x << endl;

    temp = temp2;
    gens = next;
    temp2 = next;
    next = 0;
    delete temp;
  }
  
  cout << endl << "Transformations: " << x << endl;
  return 0;
}

void print_tree(Element *a)
{
  Element *curr = a;
  while( curr ) {
    cout << curr << endl << endl;
    curr = curr->getNext();
  }
}

// will tell us if the list contains this element.
bool contains(Element *a, Element *b)
{
  Element *curr = a;
  while( curr ) {
    if( curr == b ) {
      return true;
    }
    curr = curr->getNext();
  }
  return false;
}

const int MAXINC = 15;
    
/*
 * We don't save this, if it doesn't get us closer to the goal.
 */
void generate_substrings(const Element *curr, Element *start_string,
			 Element **next)
{
  char original[ strlen(start_string->getName()) +1 ];
  char modified[ strlen(start_string->getName()) + 1 ];
  char element[ MAXINC ];		// elements are 2 char max
  char replacement[ MAXINC ];
  Element *conv = curr->getConverts();
  
  // copy the original string in.
  int x = 0;
  while( true ) {
    original[x] = start_string->getName()[x];
    if (original[x] == 0) {
      break;
    }
    ++x;
  }

  // copy the search element in
  x = 0;
  while ( true ) {
    element[x] = curr->getName()[x];
    if( element[x] == 0 ) {
      break;
    }
    ++x;
  }

  // while we have different ones to convert
  while ( conv ) {
    // copy the new string in, and set up the next loop
    x = 0;
    while ( true ) {
      replacement[x] = conv->getName()[x];
      if( replacement[x] == 0 ) {
	break;
      }
      ++x;
    }
    conv = conv->getConverts();

    // Now, search through the old string, looking for element
    // replacing each instance of it with replacement saving that
    // new string, then restore original, and find next element
    // and so on.
    int index = 0;
    while( original[index] ) {
      if( start_match(original, element, index) ) {
	// this starts a match
	replace(index, strlen(element), original, replacement, modified);
	if( *next ) {
	  *(*next) + (const char *)modified;
	} else {
	  *next = new Element( (const char *)modified );
	}
	index += strlen(element);
      }
      ++index;
    }
  }
}

/*
 * Will return true if this is the start of a match
 */
bool start_match(char *a, char *b, int index)
{
  int offset = 0;
  while( (b[offset]>0) && (a[index]>0) ) {
    if( a[index] != b[offset] ) {
      return false;
    }
    index++;
    offset++;
  }
  return true;
}

void replace(int start, int len, const char *org, const char *repl, char *mod)
{
  int x = 0;
  int y = 0;
  while( true ) {
    if ( x == start ) {
      x += len; // skip over the pattern
      while( true ) {
	mod[y] = repl[ y - start ];
	if( mod[y] == 0 ) {
	  break;
	}
	++y;
      }
    }
    mod[y] = org[x];
    if( mod[y] == 0 ) {
      // we have reached the end of the string
      break;
    }
    // increment our pointers
    ++x;
    ++y;
  }
}


/*
 * This reads the input file into the crazy structure that I have.
 * This reads the elements backwards (because we are working backwards
 * for part 2
 */
Element *read_input(Element **start_string)
{
  Element *start = 0;
  string input;
  size_t offset = 0;
  
  while( getline(cin, input) ) {
    offset = input.find(" => ");
    if( offset != std::string::npos ) {
      if( start == 0 ) {
	start = new Element( input.substr(offset + 4).c_str() );
      } else {
	*start + input.substr(offset + 4).c_str();
      }
      start->addConverts( input.substr( offset + 4 ).c_str(),
			  input.substr( 0, offset ).c_str() );
    } else {
      if( (input[0] >='A' && input[0] <= 'Z') ||
	  (input[0] >='a' && input[0] <= 'z') ) {
	*start_string = new Element( input.c_str() );
      }
    }
  }
  return start;
}
