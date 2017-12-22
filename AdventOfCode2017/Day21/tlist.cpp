#include <string>
#include <iostream>
#include "tlist.h"

TList::TList() {
  headtwo = 0;
  tailtwo = 0;
  headthree = 0;
  tailthree = 0;
}

TList::~TList() {
  while( headtwo ) {
    tailtwo = headtwo->next;
    delete headtwo;
    headtwo = tailtwo;
  }

  while( headthree ) {
    tailthree = headthree->next;
    delete headthree;
    headthree = tailthree;
  }
}

void TList::add(std::string s) {
  std::string inp = "", outp = "";
  unsigned int i, state = 0;
  transf *tmp = new transf;

  for(i = 0; i < s.length(); i++) {
    if( s[i]=='.' || s[i] =='#' ) {
      switch(state) {
      case 0:
	inp += s[i];
	break;
      case 1:
	outp += s[i];
	break;
      default:
	break;
      }
    } else {
      if( s[i] != '/' ) {
	state = 1;
      }
    }
  }

  tmp->next = 0;
  tmp->orig = inp;
  tmp->chg = outp;
  if( inp.length() == 4 ) {
    if( !headtwo ) {
      headtwo = tmp;
      tailtwo = tmp;
    } else {
      tailtwo->next = tmp;
      tailtwo = tmp;
    }
  } else {
    if( !headthree ) {
      headthree = tmp;
      tailthree = tmp;
    } else {
      tailthree->next = tmp;
      tailthree = tmp;
    }
  }
}
 
std::string TList::transform(std::string s) {
  std::string n = "";

  return n;
}
