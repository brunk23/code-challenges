#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

int main(int argc, char *argv[]) {
  int i, count;
  string output;

  i = 0;
  count = 0;
  while(count < 8) {
    output = md5( "abbhdwsy" + to_string(i));

    if( (output[0] == '0') && (output[1] == '0') && (output[2] == '0') &&
	(output[3] == '0') && (output[4] == '0') ) {
      cout << output[5];
      count++;
    }
    i++;
  }
  cout << endl;
  return 0;
}
