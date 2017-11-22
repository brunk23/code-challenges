#include <iostream>

using namespace std;

bool validTriangle(int, int, int);

bool validTriangle(int a, int b, int c) {
  if( ((a+b) > c) &&
      ((b+c) > a) &&
      ((a+c) > b) ) {
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  int a, b, c, count = 0;

  while( (cin >> a) && (cin >> b) && (cin >> c) ) {
    if( validTriangle(a,b,c) ) {
      count++;
    }
  }

  cout << "There were " << count << " valid triagles." << endl;
  
  return 0;
}
