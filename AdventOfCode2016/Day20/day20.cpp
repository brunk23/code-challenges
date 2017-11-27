#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct orderedList {
  struct orderedList* previous;
  struct orderedList* next;
  unsigned long start;
  unsigned long end;
};

orderedList *insertRange(orderedList *, unsigned long, unsigned long);
void printall(orderedList *);

/* This will put things in an ordered list */
orderedList *insertRange(orderedList *l, unsigned long s, unsigned long e) {
  orderedList *curr = l;
  orderedList *head = l;
  orderedList *range = new orderedList;

  range->start = s;
  range->end = e;
  
  while( curr ) {
    if( range->start <= curr->start ) {
      range->previous = curr->previous;

      // test could be put around above assignment to be tricky
      // but that is frowned upon in polite society.
      if( !(curr->previous) ) {
	head = range;
      } else {
	curr->previous->next = range;
      }
      range->next = curr;
      curr->previous = range;
      return head;
    }
    range->previous = curr;
    curr = curr->next;
  }
  range->next = 0;
  range->previous->next = range;
  return head;
}

void printall(orderedList *a) {
  while( a ) {
    cout << a->start << " - " << a->end << endl;
    a = a->next;
  }
}

unsigned long firstUnblocked(orderedList *l) {
  unsigned long a = 0;

  while( l ) {
    cout << l->start << " - " << l->end << ": " << a << endl;
    if( l->start <= a ) {
      if( l->end > a ) {
	a = l->end + 1;
      }
    } else {
      return a;
    }
    l = l->next;
  }
  return a;
}

int main() {
  struct orderedList *head = new orderedList;
  string input;
  unsigned long low, high;
  unsigned int i;
  bool first = true;
  
  while( cin >> input ) {
    low = 0;
    high = 0;
    for( i = 0; i < input.length(); i++ ) {
      if( input[i] == '-' ) {
	i++;
	break;
      }
      low *= 10;
      low += input[i] - '0';
    }
    for( ; i < input.length(); i++ ) {
      high *= 10;
      high += input[i] -'0';
    }
    if( first ) {
      head->previous = 0;
      head->next = 0;
      head->start = low;
      head->end = high;
      first = false;
    } else {
      head = insertRange(head, low, high);
    }
  }

  cout << "First unblocked: " << firstUnblocked(head) << endl;
  
  return 0;
}
