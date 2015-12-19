#ifndef DAY19_H
#define DAY19_h

#include <iostream>

using std::ostream;

class Element {
  friend ostream &operator<<( ostream &, const Element & );
  friend ostream &operator<<( ostream &, const Element * );
 public:
  Element();
  Element(const char *);
  Element(const Element &);
  ~Element();
  Element *getNext() const;
  Element *getConverts() const;
  const char *getName() const;
  void addConverts( const char *, const char * );
  void setNext(Element *n)
  { next = n; }
  
  // add a new element to the list, if it doesn't exist
  // already
  Element &operator+( const char * );
  
  bool operator==( const Element & ) const;
  bool operator==( const char * ) const;
  bool operator!=( const char *right ) const
  { return !(*this == right); }
  bool operator!=( const Element &right ) const
  { return !(*this == right); }

 private:
  char *name;
  Element *converts;
  Element *next;
};

#endif
