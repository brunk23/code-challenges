#include <iostream>

#define COUNT 1003

using std::cin;
using std::cout;
using std::endl;

int main() {
  int maze[COUNT], i, input, curr, prev;

  while( cin >> input ) {
    maze[i] = input;
    i++;
  }

  i = 0;
  curr = 0;
  while( (curr >= 0) && (curr < COUNT) ) {
    prev = curr;
    curr += maze[curr];
    maze[prev]++;
    i++;
    cout << i << ": " << curr << endl;
  }
  
  return 0;
}
