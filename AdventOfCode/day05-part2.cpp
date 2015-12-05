#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

bool niceString(const char *);

int main()
{
  int count = 0;
  string input;

  while ( getline(cin, input) ) {
    if ( niceString(input.c_str()) ) {
      count++;
      cout << input << " is nice." << endl;
    } else {
      cout << input << " is naughty." << endl;
    }
  }
  cout << count << " strings were nice." << endl;

  return 0;
}

// Will misbehave if the string isn't null terminated and
// has fewer than 3 chars.
bool niceString(const char *test) {
  int count;
  bool repeatChar = false;
  bool repeatPair = false;
  for (count = 2; test[count] != 0; ++count) {
    if ( test[count] == test[count-2] ) {
      repeatChar = true;
      break;
    }
  }

  for (count = 2; test[count] != 0; ++count) {
    for (int x = count+1; test[x] != 0; ++x) {
      if ( (test[count] == test[x]) &&
	   (test[count+1] == test[x+1])) {
	cout << test[count] << test[count+1] << " == "
	     << test[x] << test[x+1];
	repeatPair = true;
	break;
      }
    }
    if ( repeatPair ) {
      break;
    }
  }
  
  if ( repeatPair && repeatChar ) {
    return true;
  }
  return false;
}
