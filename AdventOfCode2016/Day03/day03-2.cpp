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
  int a1, a2, a3, b1, b2, b3, c1, c2, c3, count = 0;

  while( (cin >> a1) && (cin >> b1) && (cin >> c1) &&
	 (cin >> a2) && (cin >> b2) && (cin >> c2) &&
	 (cin >> a3) && (cin >> b3) && (cin >> c3) ) {
    if( validTriangle(a1,a2,a3) ) {
      count++;
    }
    if( validTriangle(b1,b2,b3) ) {
      count++;
    }
    if( validTriangle(c1,c2,c3) ) {
      count++;
    }
  }

  cout << "There were " << count << " valid triagles." << endl;
  
  return 0;
}
