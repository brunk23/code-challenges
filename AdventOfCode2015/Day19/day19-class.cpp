// methods for class for day 19

#include <iostream>
#include <string>
#include <cassert>
#include "day19.h"

// This shouldn't be called, but just in case
Element::Element()
{
  name = 0;
  converts = 0;
  next = 0;
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

// This is the constructor we will use most often
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

// Free the memory from all the stuff, this really needs to descend
// into converts and delete all that junk.
Element::~Element(){
  if( name > 0 ) {
    delete [] name;
  }
  // The following should delete the whole branch, because when
  // each object is deleted, it will call this destructor on itself
  // and delete any objects beneath it.
  if( converts ) {
    delete converts;
  }
}

// find the name n, and add the conversion b
void Element::addConverts( const char *n, const char *b )
{
  Element *curr = this;
  while( *curr != n ) {
    curr = curr->next;
    assert( curr != 0 );	// The element isn't on the list
  }
  while( curr->converts ) {
    curr = curr->converts;
  }
  curr->converts = new Element( b );
}

Element *Element::getNext() const
{
  return next;
}

Element *Element::getConverts() const
{
  return converts;
}

const char *Element::getName() const
{
  return name;
}

// Pretty print each element and possible outcomes
ostream &operator<<( ostream &output, const Element *a )
{
  Element *next = a->converts;
  output << a->name << " => { ";
  while (next) {
    output << next->name << " ";
    next = next->converts;
  }
  output << "}";
  return output;
}

ostream &operator<<( ostream &output, const Element &a )
{
  Element *next = a.converts;
  output << a.name << " => { ";
  while (next) {
    output << next->name << " ";
    next = next->converts;
  }
  output << "}";
  return output;
}

// add elements to the current starting object
Element &Element::operator+( const char *n )
{
  Element *curr = this;
  while ( true ) {
    if( *curr == n ) {
      break;			// already in tree
    }
    if( curr->next == 0 ) {	// not in tree, add
      curr->next = new Element( n );
      break;
    }
    curr = curr->next;
  }
  return *this;
}

// comparison operators (only compares names)
bool Element::operator==( const Element &other ) const
{
  int x = strcmp(name, other.name);
  if( x == 0 ) {
    return true;
  }
  return false;
}

// comparison operator (only compares name and string)
bool Element::operator==( const char *b ) const
{
 int x = strcmp(this->name, b);
  if( x == 0 ) {
    return true;
  }
  return false;
} 
