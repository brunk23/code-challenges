#include <iostream>

#define COUNT 1099

using std::cin;
using std::cout;
using std::endl;

int main() {
  int maze[COUNT], i = 0, input, curr, prev;
  int max;

  while( cin >> input ) {
    maze[i] = input;
    i++;
  }
  max = i;
  i = 0;
  curr = 0;
  while( (curr >= 0) && (curr < max) ) {
    prev = curr;
    curr += maze[curr];
    maze[prev]++;
    i++;
    // cout << i << ": " << curr << endl;
  }
  cout << i << endl;
  return 0;
}
