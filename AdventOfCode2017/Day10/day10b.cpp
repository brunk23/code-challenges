#include <iostream>
#include <string>
#include <sstream>

#define SIZE 256

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::getline;

void swap( int [SIZE], unsigned int, unsigned int);
void printlist(int [SIZE]);
void printdigit(int);

void printdigit(int n) {
  char h, l;
  h = n / 16;
  l = n % 16;
  if( h < 10 ) {
    h += '0';
  } else {
    h -= 10;
    h += 'a';
  }
  if( l < 10 ) {
    l += '0';
  } else {
    l -= 10;
    l += 'a';
  }
  cout << h << l;
}

void printlist(int list[SIZE]) {
  unsigned int i;
  unsigned int curr = 0;

  cout << "In printlist: ";
  
  for( i = 0; i < SIZE; i++ ) {
    curr ^= list[i];
    if( 15 == (i % 16) ) {
      printdigit(curr);
      curr = 0;
    }
  }
  cout << endl << endl;
}

void swap(int list[SIZE], unsigned int start, unsigned int length) {
  unsigned int i,j;
  int tmp;
  i = start;
  j = start + length - 1;
  while( j > i ) {
    tmp = list[ i % SIZE ];
    list[ i % SIZE ] = list[ j % SIZE];
    list[ j % SIZE ] = tmp;
    i++;
    j--;
  }
}

int main() {
  int list[SIZE];
  unsigned int i, len, step=0, loc = 0, loop;
  string input;
  
  for( i = 0; i < SIZE; i++ ) {
    list[i] = i;
  }

  if( !getline(cin, input) ) {
    cerr << "Unable to get input" << endl;
  }

  for( loop = 0; loop < 64; loop++ ) {
    for( i = 0; i < input.length(); i++ ) {
      len = input[i];
      swap(list, loc, len);
      loc = loc + len + step;
      loc %= SIZE;
      step++;
    }
    swap( list, loc, 17 );
    loc = loc + 17 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 31 );
    loc = loc + 31 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 73 );
    loc = loc + 73 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 47 );
    loc = loc + 47 + step;
    loc %= SIZE;
    step++;
    swap( list, loc, 23 );
    loc = loc + 23 + step;
    loc %= SIZE;
    step++;
  }

  printlist(list);
  
  return 0;
}
