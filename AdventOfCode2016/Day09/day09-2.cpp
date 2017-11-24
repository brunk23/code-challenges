#include <iostream>
#include <string>

using namespace std;

long long datalen(string);

long long datalen(string data) {
  int i, datlength, repeat;
  long long count = 0;

  for( i = 0; i < data.length(); i++ ) {
    if( data[i] == '(' ) {
      datlength = 0;
      repeat = 0;
      i++;
      while(data[i] != 'x') {
	datlength *= 10;
	datlength += data[i] - '0';
	i++;
      }
      i++;
      while(data[i] != ')') {
	repeat *= 10;
	repeat += data[i] - '0';
	i++;
      }
      count += repeat * datalen(data.substr(i+1, datlength));
      i += datlength;
      continue;
    }
    count++;
  }
  return count;
}

int main(int argc, char *argv[]) {
  long long count = 0;
  string input;
  
  while( cin >> input ) {
    count += datalen(input);
  }
  
  cout << "Decompressed length = " << count << endl;
  return 0;
}
