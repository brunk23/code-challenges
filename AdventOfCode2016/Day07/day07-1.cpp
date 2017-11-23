#include <iostream>
#include <string>

using namespace std;

bool supportsTLS(string);

bool supportsTLS(string inp) {
  int insidebrackets = 0, i;
  bool TLS = false;
  
  for(i = 0; i < inp.length() - 3; i++) {
    if( inp[i] == '[' ) {
      insidebrackets++;
    }
    if( inp[i] == ']' ) {
      insidebrackets--;
    }
    if( (inp[i] == inp[i+3]) && (inp[i+1] == inp[i+2]) && (inp[i] != inp[i+1]) ) {
      if( insidebrackets > 0 ) {
	return false;
      }
      TLS = true;
    }
  }

  if( TLS ) {
    cout << inp << endl;
  }
  return TLS;
}

int main(int argc, char *argv[]) {
  string foo;
  int count=0;
  
  while( cin >> foo ) {
    if( supportsTLS(foo) ) {
      count++;
    }
  }

  cout << count << " supported TLS." << endl;
  return 0;
}
