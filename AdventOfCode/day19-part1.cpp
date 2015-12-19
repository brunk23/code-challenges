#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ostream;

class Element {
  friend ostream &operator<<( ostream &, const Element & );
  friend ostream &operator<<( ostream &, const Element * );
public:
  Element();
  Element(const char *);
  Element(const Element &);
  ~Element();
  bool operator==( const Element & );
  bool operator==( const char *);
  
  char *name;
  Element *converts;
  Element *next;
};

ostream &operator<<( ostream &output, const Element *a )
{
  Element *next = a->converts;
  cout << a->name << " => { ";
  while (next) {
    cout << next->name << " ";
    next = next->converts;
  }
  cout << "}";
  return output;
}

ostream &operator<<( ostream &output, const Element &a )
{
  Element *next = a.converts;
  cout << a.name << " => { ";
  while (next) {
    cout << next->name << " ";
    next = next->converts;
  }
  cout << "}";
  return output;
}

Element::Element(const char *n)
{
  int x = strlen(n);
  name = new char[ x+1 ];
  for(int y = 0; y <= x; ++y) {
    name[y] = n[y];
  }
  converts = 0;
  next = 0;
}

bool Element::operator==( const Element &other )
{
  int x = strcmp(name, other.name);
  if( x == 0 ) {
    return true;
  }
  return false;
}

bool Element::operator==( const char *b )
{
 int x = strcmp(this->name, b);
  if( x == 0 ) {
    return true;
  }
  return false;
} 

// this shouldn't cause issues
Element::Element(const Element &init)
{
  int x = strlen( init.name );
  name = new char[ x+1 ];
  for(int y = 0; y <= x; ++y) {
    name[y] = init.name[y];
  }
  converts = init.converts;
  next = init.next;
}

// This shouldn't be called
Element::Element()
{
  name = 0;
  converts = 0;
  next = 0;
}

// Free the memory from all the stuff, this really needs to descend
// into converts and delete all that junk.
Element::~Element(){
  if( name > 0 ) {
    delete [] name;
  }
}

Element *read_input();

int main()
{
  Element *head, *curr;

  head=read_input();

  curr = head;
  int x = 0;
  
  while ( curr ) {
    cout << x++ << "->name: " << curr << endl;
    curr = curr->next;
  }
  return 0;
}

/*
 * This reads the input file into the crazy ass structure that I have.
 */
Element *read_input()
{
  Element *start = 0, *curr, *evolve;
  string input;
  size_t offset = 0;
  
  while( getline(cin, input) ) {
    offset = input.find(" => ");
    if( offset != std::string::npos ) {
      if( start > 0 ) {
	curr = start;
	while ( true ) {
	  if( *curr == input.substr(0,offset).c_str() ) {
	    break;
	  }
	  if( curr->next == 0 ) {
	    curr->next = new Element( input.substr(0,offset).c_str() );
	    curr = curr->next;
	    break;
	  }
	  curr = curr->next;
	}
      } else {
	start = new Element( input.substr(0,offset).c_str() );
	curr = start;
      }
      evolve = curr;
      while ( evolve->converts ) {
	evolve = evolve->converts;
      }
      evolve->converts = new Element( input.substr( offset+4 ).c_str() );
    }
  }
  return start;
}
