#include <iostream>
#include <string>

using std::cout;
using std::getline;
using std::cin;
using std::endl;
using std::string;

bool validPassword(string);
bool strequal(string, string);

bool strequal( string a, string b ) {
  int i;
  if( a.length() != b.length() ) {
    return false;
  }
  for( i = 0; i < a.length(); i++) {
    if( a[i] != b[i] ) {
      return false;
    }
  }
  return true;
}

bool validPassword(string s) {
  int i, beg, end;
  string words[30];

  for( i = 0; i < 30; i++ ) {
    words[i] = "";
  }
  
  i = 0;
  beg = 0;
  for( end = 0; end < s.length(); end++ ) {
    if( s[end] >= 'a' && s[end] <= 'z' ) {
      continue;
    }
    words[i] = s.substr(beg, end - beg);
    beg = end + 1;
    i++;
  }
  words[i] = s.substr(beg, end - beg);
  i++;

  for( beg = 0; beg < (i - 1); beg++ ) {
    for( end = beg + 1; end < i; end++ ) {
      if( strequal( words[beg], words[end] ) ) {
	return false;
      }
    }
  }

  return true;
}

int main() {
  string s;
  int count = 0;
  
  while( getline(cin, s) ) {
    if( validPassword( s ) ) {
      count++;
    }
  }
  
  cout << "The number of valid passwords was " << count << endl;
  
  return 0;
}
