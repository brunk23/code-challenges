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
void generate_substrings(const Element *curr, Element *start_string,
			 const char *goal);
void replace(int start, int len, const char *org, const char *repl, char *mod);
bool contains(Element *a, Element *b);
void print_tree(Element *a);

int main()
{
  Element *head, *curr;
  Element *final_string;
  Element start_string("e"), *gens;
  
  head = read_input( &final_string );

  curr = head;

  // head and curr represent possible transformations
  // start_string and gened are the generated strings

  int x = 0, depth = 0, count;
  gens = &start_string;
  while ( !(contains(&start_string, final_string)) ) {
    while ( curr ) {
      depth = 0;
      while ( gens ) {
	depth++;
	gens = gens->getNext();
      }
      count = 0;
      gens = &start_string;
      while ( gens && count <= depth ) {
	generate_substrings(curr, gens, final_string->getName());
	gens = gens->getNext();
	++count;
      }
      curr = curr->getNext();
    }
    ++x;			// didn't make it this time
    curr = head;		// reset the conversions
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
  Element *prev = a;
  int maxlen = strlen( b->getName() );
  while( curr ) {
    if( strlen( curr->getName() ) > maxlen ) {
      if( prev != curr ) {
	prev->setNext( curr->getNext() );
	delete curr;
	curr = prev;
      }
    }
    if( *curr == *b ) {
      cout << *curr << " == " << *b << endl;
      return true;
    }
    prev = curr;
    curr = curr->getNext();
  }
  return false;
}

const int MAXINC = 10;

int score(const char *a, const char *b)
{
  int x = 0;
  int y = 0;
  int total = 0;
  while( true ) {
    if( (a[x] == 0) && (b[y] == 0) ) {
      break;
    }
    if( (a[x] != 0) && (b[y] != 0) ) {
      if( a[x] > b[y] ) {
	total += a[x++] - b[y++];
      } else {
	total += b[y++] - a[x++];
      }
    } else {
      if( a[x] != 0 ) {
	total += a[x++];
      } else {
	total += b[y++];
      }
    }
  }
  return total;
}
    
/*
 * We don't save this, if it doesn't get us closer to the goal.
 */
void generate_substrings(const Element *curr, Element *start_string,
			 const char *goal)
{
  int start_score, new_score;
  char original[ strlen(start_string->getName()) +1 ];
  char modified[ strlen(start_string->getName()) + 1 + MAXINC ];
  char element[ 3 ];		// elements are 2 char max
  char replacement[ MAXINC ];
  Element *conv = curr->getConverts();

  start_score=score(start_string->getName(), goal);
  
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
      if( element[1] ) {
	if( (original[index + 1 ] == element[1]) &&
	    (original[index] == element[0]) ) {
	  // two char match
	  replace(index, 2, original, replacement, modified);
	  new_score = score( modified, goal );
	  if( new_score <= start_score ) {
	    // only add strings that bring us closer
	    *start_string + (const char *)modified;
	  }
	  index += 1;
	}
      } else {
	if(original[index] == element[0]) {
	  // one char match
	  replace(index, 1, original, replacement, modified);
	  *start_string + (const char *)modified;
	}
      }
      ++index;
    }
  }
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
	start = new Element( input.substr(0,offset).c_str() );
      } else {
	*start + input.substr(0,offset).c_str();
      }
      start->addConverts( input.substr(0,offset).c_str(),
			  input.substr( offset+4 ).c_str() );
    } else {
      if( (input[0] >='A' && input[0] <= 'Z') ||
	  (input[0] >='a' && input[0] <= 'z') ) {
	*start_string = new Element( input.c_str() );
      }
    }
  }
  return start;
}
