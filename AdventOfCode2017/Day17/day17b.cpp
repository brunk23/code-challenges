#include <iostream>

using std::cout;
using std::endl;

class CBuff {
private:
  int stepsize;
  int pos;
  int curr;
  int old;
  
public:
  CBuff(int size) {
    stepsize = size;
    
    curr = 0;
    pos = 0;
    old = -1;
  }

  int step() {
    int i;
    curr++;

    i = (stepsize + pos) % curr;

    if( i == 0 ) {
      old = curr;
    }
    pos = i + 1;
    
    return old;
  }
};

int main() {
  int i, c;
  // CBuff b(328);
  CBuff b(355);
  
  for(i = 1; i < 50000000; i++ ) {
    c = b.step();
  }
  cout << c << endl;
  return 0;
}
  
