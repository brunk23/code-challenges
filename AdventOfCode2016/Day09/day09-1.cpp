#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  bool inMarker = false, inData = false;
  int count = 0, datlength = 0, i, repeat = 0;
  string input;
  
  while( cin >> input ) {
    if( inData ) {
      cout << "WARNING DATA WRAPS LINES." << endl;
    }
    for( i = 0; i < input.length(); i++ ) {
      // Ignore data -- we accounted for it already
      if( inData ) {
	datlength--;
	if(datlength == 1) {
	  inData = false;
	}
	continue;
      }

      if( input[i] == '(' ) {
	datlength = 0;
	repeat = 0;
	inMarker = true;
	i++;
	while(input[i] != 'x') {
	  datlength *= 10;
	  datlength += input[i] - '0';
	  i++;
	}
	i++;
	while(input[i] != ')') {
	  repeat *= 10;
	  repeat += input[i] - '0';
	  i++;
	}
	i++;
	count += repeat * datlength;
	inMarker = false;
	inData = true;
	continue;
      }

      if( !inMarker && !inData ) {
	count++;
      } else {
	cout << "ERROR: We got here while inData or inMarker!" << endl;
      }
    }
  }

  cout << "Decompressed length = " << count << endl;
  return 0;
}
