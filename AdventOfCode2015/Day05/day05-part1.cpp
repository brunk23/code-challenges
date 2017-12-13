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

// Will misbehave if the string isn't null terminated
bool niceString(const char *test) {
  int count;
  int vowelcount = 0;
  char lastChar = 0;
  bool repeat = false;
  bool naughty = false;
  for ( count = 0; test[count] != 0; ++count) {

    // If we get one of the four naughty strings, quit immediately
    if ( (lastChar == 'a' && test[count] == 'b') ||
	 (lastChar == 'c' && test[count] == 'd') ||
	 (lastChar == 'p' && test[count] == 'q') ||
	 (lastChar == 'x' && test[count] == 'y') ) {
      naughty = true;
      break;
    }

    // Make sure we check to see if we repeat.
    if ( lastChar == test[count] ) {
      repeat = true;
    }
    
    switch ( test[count] ) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      vowelcount++;
      break;
    default:
      break;
    }
    lastChar = test[count];
  }
  if ( naughty ) {
    return false;
  }
  if ( (vowelcount >= 3) && repeat ) {
    return true;
  }
  return false;
}
