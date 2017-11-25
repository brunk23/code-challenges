#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string chcksum(string);

string chcksum(string a) {
  string n = "";
  int i;
  for(i = 0; i < a.length()-1; i += 2 ) {
    if( a[i] == a[i+1] ) {
      n += '1';
    } else {
      n += '0';
    }
  }
  if( (n.length() % 2) == 0 ) {
    n = chcksum(n);
  }
  return n;
}

int main() {
  string input = "01000100010010111";
  string tmp;
  string current = "";
  string checksum = "";
  int i;
  
  current = input;
  while( current.length() <  35651584) {
    tmp = current;
    std::reverse(tmp.begin(), tmp.end());
    for( i = 0; i < tmp.length(); i++ ) {
      if( tmp[i] == '1' ) {
	tmp[i] = '0';
      } else {
	tmp[i] = '1';
      }
    }
    current = current + "0" + tmp;
  }

  current = current.substr(0, 35651584);
  current = chcksum(current);
  cout << current << endl;
  
  
  return 0;
}
