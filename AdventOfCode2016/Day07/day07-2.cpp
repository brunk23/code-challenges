#include <iostream>
#include <string>

using namespace std;

bool supportsSSL(string);
bool hasBAB(string, char []);

bool hasBAB(string inp, char possible[4]) {
  int insidebrackets = 0, i;
  for(i = 0; i < inp.length() - 2; i++) {
    if( inp[i] == '[' ) {
      insidebrackets++;
      continue;
    }
    if( inp[i] == ']' ) {
      insidebrackets--;
      continue;
    }
    if( insidebrackets == 0 ) {
      continue;
    }
    if( (inp[i] == possible[0]) && (inp[i+1] == possible[1]) &&
	(inp[i+2] == possible[2]) ) {
      return true;
    }
  }
  
  return false;
}

bool supportsSSL(string inp) {
  int insidebrackets = 0, i;
  char possible[4] = {0,0,0,0};
  
  for(i = 0; i < inp.length() - 2; i++) {
    if( inp[i] == '[' ) {
      insidebrackets++;
      continue;
    }
    if( inp[i] == ']' ) {
      insidebrackets--;
      continue;
    }
    if( insidebrackets > 0 ) {
      continue;
    }
    if( (inp[i] == inp[i+2]) && (inp[i+1] != inp[i]) ) {
      possible[0] = inp[i+1];
      possible[1] = inp[i];
      possible[2] = inp[i+1];
      if( hasBAB(inp, possible) ) {
	return true;
      }
    }
  }
  
  return false;
}

int main(int argc, char *argv[]) {
  string foo;
  int count=0;
  
  while( cin >> foo ) {
    if( supportsSSL(foo) ) {
      count++;
    }
  }

  cout << count << " supported SSL." << endl;
  return 0;
}
