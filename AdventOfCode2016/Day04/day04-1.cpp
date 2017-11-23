#include <iostream>
#include <string>

int validRoom(std::string);

using namespace std;

int validRoom(string ident) {
  int count[26], i, highest, curr, value=0;
  int index;
  
  // We use this to count the amount of chars.
  for(i = 0; i < 26; i++) {
    count[i] = 0;
  }
  highest = 0;

  // Read the character codes and count characters.
  for(i = 0; i < ident.length(); i++) {
    if( ident[i] == '-' ) {
      continue;
    }
    if( ident[i] >= '0' && ident[i] <= '9' ) {
      // we hit a number, break out -- DO NOT RESET i.
      break;
    }
    curr = ident[i] - 'a';
    if( (curr < 0) || (curr > 25) ) {
      // ERROR -- SHOULD NOT HAPPEN
      return -1;
    }
    count[curr]++;
    if( count[curr] > highest ) {
      highest = count[curr];
    }
  }

  for( ; i < ident.length(); i++) {
    if( ident[i] == '[' ) {
      // we hit the checksum
      i++;
      break;
    }
    value *= 10;
    value += ident[i] - '0';
  }

  // Here we need a loop that checks to make sure the
  // highest value character is under i.
  while( i < ident.length() ) {
    for( index = 0; index < 26; index++ ) {
      if( count[index] == highest ) {
	if( (index+'a') == ident[i] ) {
	  i++;
	  if(ident[i] == ']') {
	    return value;
	  }
	} else {
	  return 0;
	}
      }
    }
    highest--;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  string input;
  int sum = 0, temp;
;

  while( cin >> input ) {
    temp = validRoom(input);
    if( temp == -1 ) {
      cerr << "Something went wrong!" << endl;
      cerr << input << endl;
      return 1;
    }
    cout << input << ": " << temp << endl;
    sum += temp;
  }

  cout << "The sum of sector ids was: " << sum << endl;
  
  return 0;
}
