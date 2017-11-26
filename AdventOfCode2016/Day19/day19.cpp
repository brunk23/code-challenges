#include <iostream>

using namespace std;

#define ELVES 3012210

int main() {
  int i, count = ELVES;
  char elf[ELVES];
  bool stealing = false;
  
  for(i = 0; i < ELVES; i++) {
    elf[i] = 1;
  }

  while(count > 1) {
    for(i = 0; i < ELVES; i++) {
      if( elf[i] == 0 ) {
	continue;
      }
      if( elf[i] == 1 ) {
	if( stealing ) {
	  stealing = false;
	  elf[i] = 0;
	  count--;
	} else {
	  stealing = true;
	}
      }
    }
  }

  for( i = 0; i < ELVES; i++ ) {
    if( elf[i] == 1 ) {
      cout << i+1 << endl;
      break;
    }
  }
  return 0;
}
