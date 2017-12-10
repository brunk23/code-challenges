#include <iostream>
#include <string>
#include <sstream>

#define SIZE 256

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

void swap( int [SIZE], unsigned int, unsigned int);
void printlist(int [SIZE]);

void printlist(int list[SIZE]) {
  unsigned int i;

  for( i = 0; i < SIZE; i++ ) {
    cout << list[i] << "\t";
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
  unsigned int i, len, step=0, loc = 0;
  string input;
  
  for( i = 0; i < SIZE; i++ ) {
    list[i] = i;
  }

  if( !(cin >> input) ) {
    cerr << "Unable to get input" << endl;
  }
  for( i = 0; i < input.length(); i++ ) {
    if( input[i] == ',' ) {
      input[i] = ' ';
    }
  }
  stringstream s(input);
  while (s >> len ) {
    swap(list, loc, len);
    loc = loc + len + step;
    loc %= SIZE;
    step++;
    // printlist(list);
  }

  cout << list[0] * list[1] << endl;
  
  return 0;
}
