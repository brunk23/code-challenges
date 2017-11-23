#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

int main(int argc, char *argv[]) {
  int i, count;
  char code[9];
  string output;

  for(i = 0; i < 9; i++) {
    code[i] = 0;
  }
  
  i = 0;
  count = 0;
  while(count < 8) {
    output = md5( "abbhdwsy" + to_string(i));

    if( (output[0] == '0') && (output[1] == '0') && (output[2] == '0') &&
	(output[3] == '0') && (output[4] == '0') ) {
      if( (output[5] >= '0') && (output[5] <= '7') && (code[ output[5]-'0' ] == 0) ) {
	count++;
	code[ output[5]-'0' ] = output[6];
      }
    }
    i++;
  }
  cout << code << endl;
  return 0;
}
