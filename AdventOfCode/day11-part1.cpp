#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

bool valid_password(const char *);
void inc_passwd(char *pass);

const int PASS_SIZE = 9;

int main()
{
	int count = 0;
	char passwd[PASS_SIZE] = "zzzzzzzh";;

	do {
		inc_passwd(passwd);	
		cout << passwd << " is the next valid password." << endl;
	} while ( !valid_password( passwd ) );
	cout << passwd << " is the next valid password." << endl;

	return 0;
}

/*
 * Tested and works
 */
void inc_passwd(char *pass)
{
	int x = 0;
	for( ; pass[x] !=0; ++x)
		;	// empty loop
	--x;
	while (true) {
		if( pass[x] != 'z' ) {
			pass[x]++;
			break;
		}
		pass[x]='a';
		--x;
		if( x < 0 ) {
			cout << "\n\nOVERFLOW ERROR\nString Reset\n\n";
			break;
		}
	}
}	

// Will misbehave if the string isn't null terminated and
// has fewer than 3 chars.
bool valid_password(const char *test) {
  int count = 0;
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
