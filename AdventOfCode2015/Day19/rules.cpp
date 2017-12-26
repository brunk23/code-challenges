#include <iostream>
#include <string>
#include "rules.h"

Rules::TRule *Rules::head = 0;
Rules::TRule *Rules::tail = 0;
int Rules::instances = 0;

Rules::Rules() {
  instances++;
  curr = 0;
}

Rules::~Rules() {
  instances--;
  if( instances == 0 ) {
    while( head ) {
      tail = head->next;
      delete head;
      head = tail;
    }
  }
}

void Rules::reset() {
  curr = head;
}

void Rules::next() {
  if( curr != 0 ) {
    curr = curr->next;
  }
}

/*
 * This looks for curr->right in the string
 * a, starting at start.
 */
int Rules::location(std::string a, int start) {
  if( curr == 0 ) {
    return -1;
  }
  return 0;
}

/*
 * This would be more effecient, if it sorted things.
 */
void Rules::add(std::string lft, std::string rght) {
  TRule *tmp = new TRule;
  tmp->next = 0;
  tmp->right = rght;
  tmp->lenR = rght.length();
  tmp->left = lft;
  tmp->lenL = lft.length();

  if( head == 0 ) {
    head = tmp;
    tail = tmp;
  } else {
    tail->next = tmp;
    tail = tmp;
  }
}
