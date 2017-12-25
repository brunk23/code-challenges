#include <iostream>

using std::cout;
using std::endl;

class CBuff {
private:
  int len;
  int stepsize;
  int pos;
  int curr;
  int *buffer;

  void shiftup(int start) {
    int i;
    for( i = len-2; i >= start; i-- ) {
      buffer[i+1] = buffer[i];
    }
  }
  
public:
  CBuff(int size) {
    int i;
    len = 2018;
    buffer = new int[len];
    stepsize = size;
    
    curr = 0;
    pos = 0;
    buffer[0] = 0;
    for( i = 1; i < len; i++ ) {
      buffer[i] = -1;
    }
  }

  int step() {
    int i;
    curr++;

    i = (stepsize + pos) % curr;

    if( buffer[i+1] != -1 ) {
      shiftup(i+1);
    }
    buffer[i+1] = curr;
    pos = i+1; 

    return buffer[pos+1];
  }
};

int main() {
  int i;
  // CBuff b(328);
  CBuff b(355);
  
  for(i = 0; i < 2017; i++ ) {
    cout << i+1 << ": " << b.step() << endl;
  }
  return 0;
}
  
