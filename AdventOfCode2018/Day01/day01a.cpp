#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main(int argc, char *argv[]) {
  long pos=0,neg=0,tmp;
  string buff;

  while(getline(cin,buff)) {
    tmp = 0;
    for(int i=1; i < buff.length(); i++) {
      tmp *= 10;
      tmp += buff[i] - '0';
    }
    if( buff[0] == '+' ) {
      pos += tmp;
    } else {
      neg += tmp;
    }
  }

  cout << "Pos: " << pos << endl;
  cout << "Neg: " << neg << endl;

  if( pos < neg ) {
    cout << "-" << (neg-pos) << endl;
  } else {
    cout << "+" << (pos-neg) << endl;
  }
  
  return 0;
}
