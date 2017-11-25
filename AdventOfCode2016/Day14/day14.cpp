#include <iostream>
#include <string>
#include "md5.h"

using std::string;
using std::cout;
using std::endl;

struct hash {
  int number;
  string str;
  struct hash *next;
};

hash *nexthash(int);
void printall(hash *);
bool checkcurr(hash *);
bool isValid(hash *, char);

void printall(hash *head) {
  hash *curr = head;

  while( curr != 0 ) {
    std::cout << curr->number << ": " << curr->str << std::endl;
    curr = curr->next;
  }
}

bool isValid(hash *curr, char a) {
  int i;

  while( curr ) {
    for( i = 0; i < curr->str.length()-4; i++) {
      if( (a == curr->str[i]) && (a == curr->str[i+1]) &&
	  (a == curr->str[i+2]) && (a == curr->str[i+3]) &&
	  (a == curr->str[i+4]) ) {
	cout << "\nIndex " << curr->number << " [" << curr->str << "] was valid?" << endl;
	return true;
      }
    }
    curr = curr->next;
  }
  return false;
}

bool checkcurr(hash *head) {
  int i;

  for(i = 0; i < head->str.length()-2; i++) {
    if( (head->str[i] == head->str[i+1]) &&
	(head->str[i] == head->str[i+2]) ) {
      if( isValid(head->next, head->str[i]) ) {
	return true;
      } else {
	return false;
      }
    }
  }
  return false;
}

hash *nexthash(int numb) {
  hash *n = (struct hash *)malloc(sizeof(struct hash));
  string s = "cuanljph";
  
  n->number = numb;
  n->next = 0;
  n->str = md5(s + std::to_string(numb));
  return n;
}

int main() {
  hash *head;
  hash *curr;
  int i, count = 0;
  
  head = nexthash(0);
  curr = head;
  for( i = 1; i <= 1000; i++ ) {
    curr->next = nexthash(i);
    curr = curr->next;
  }
  
  while( count < 64 ) {
    if(checkcurr(head)) {
      count++;
      cout << "Index " << head->number << " [" << head->str << "] was valid." << endl;
    }
    curr = head->next;
    free(head);
    head = curr;
    while( curr->next ) {
      curr = curr->next;
    }
    curr->next = nexthash( curr->number+1 );
  }
  
  return 0;
}
