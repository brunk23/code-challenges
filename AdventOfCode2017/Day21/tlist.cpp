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

  //  std::cerr << inp << " -> " << outp << std::endl;

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

bool TList::cmpA(char x[3][3], char y[3][3], int n) {
  int i, j;
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      if( x[i][j] != y[i][j] ) {
	return false;
      }
    }
  }
  return true;
}

void TList::cpA(char src[3][3], char dest[3][3], int n) {
  int i, j;
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      dest[i][j] = src[i][j];
    }
  }
}

void TList::flipA(char src[3][3], char dest[3][3], int n) {
  if( n == 2 ) {
    dest[0][0] = src[0][1];
    dest[0][1] = src[0][0];
    dest[1][0] = src[1][1];
    dest[1][1] = src[1][0];
    return;
  }
  dest[0][0] = src[0][2];
  dest[0][1] = src[0][1];
  dest[0][2] = src[0][0];
  dest[1][0] = src[1][2];
  dest[1][1] = src[1][1];
  dest[1][2] = src[1][0];
  dest[2][0] = src[2][2];
  dest[2][1] = src[2][1];
  dest[2][2] = src[2][0];
}

void TList::printA(char src[3][3], int n) {
  int i, j;

  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      std::cout << src[i][j];
    }
    std::cout << std::endl;
  }
}

void TList::rotA(char src[3][3], char dest[3][3], int n) {
  int i, j;

  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      dest[i][j] = src[n-j-1][i];
    }
  }
}

bool TList::isMatch(std::string a, std::string b) {
  int n = 3, i, j, k;
  char ax[3][3], bx[3][3], tmp[3][3];

  if( a.length() == 4 ) {
    n = 2;
  } else {
    if( a[4] != b[4] ) {
      return false;
    }
  }
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      ax[i][j] = a[i*n+j];
      bx[i][j] = b[i*n+j];
    }
  }
  if( cmpA(ax,bx,n) ) {
    return true;
  }
  for( k = 0; k < 4; k++ ) {
    flipA(bx,tmp,n);
    if( cmpA(ax,tmp,n) ) {
      return true;
    }
    rotA(bx,tmp,n);
    if( cmpA(ax,tmp,n) ) {
      return true;
    }
    cpA(tmp,bx,n);
  }

  return false;
}

std::string TList::transform(std::string s) {
  std::string n = "";
  transf *hd = headthree;
  transf *curr = 0;

  if( s.length() == 4 ) {
    hd = headtwo;
  }
  curr = hd;

  while( curr ) {
    if( isMatch(s, curr->orig) ) {
      break;
    }
    curr = curr->next;
  }
  if( !curr ) {
    n = "FATAL: No match!";
    return n;
  }
  n = curr->chg;
  //  std::cout << curr->orig << " -> " << n << std::endl;
  return n;
}
  
