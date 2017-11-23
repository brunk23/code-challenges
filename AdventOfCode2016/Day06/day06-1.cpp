#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  string input;
  int count[8][26],index,alpha, max, location;
  char a;

  for(index = 0; index < 8 ; index++) {
    for(alpha = 0; alpha < 26; alpha++) {
      count[index][alpha]=0;
    }
  }

  while( cin >> input ) {
    for(index = 0; index < 8; index++) {
      count[index][input[index]-'a']++;
    }
  }

  for(index = 0; index < 8; index++) {
    max = count[index][0];
    location = 0;
    for(alpha = 1; alpha < 26; alpha++) {
      if( count[index][alpha] > max ) {
	max = count[index][alpha];
	location=alpha;
      }
    }
    a = 'a';
    a += location;
    cout << a;
  }

  cout << endl;
  
  return 0;
}
