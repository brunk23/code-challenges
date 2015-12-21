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
	char passwd[PASS_SIZE] = "hxbxwxba";;

	for(int x = 0; x < 2; x++) {
		do {
			inc_passwd(passwd);	
		} while ( !valid_password( passwd ) );
	}
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
			// premature optimization
			switch (pass[x]) {
			case 'i':
			case 'o':
			case 'l':
				pass[x]++;
				break;
			default:
				break;
			}
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
 	int increase_chars = 0;
	int repeat_count = 0;
	bool straight = false;
	bool repeatChar = false;
	bool forbiddenchar = false;

	// Check for forbidden chars
	for (count = 0; test[count] != 0; ++count) {
		switch ( test[count] ) {
		case 'i':
		case 'o':
		case 'l':
			return forbiddenchar;
			break;
		default:
			break;
		}
	}
	
	// test for a run of 3+
	for (count = 1; test[count] != 0; ++count) {

		if ( test[count]-1 == test[count-1] ) {
			increase_chars++;
			if (increase_chars == 2) {
				straight = true;
				break;
			};
		} else {
			increase_chars = 0;
		}
	}

	for (count = 1; test[count] != 0; ++count) {
		if(test[count] == test[count-1]) {
			repeat_count++;
			count++;
		}
		if(repeat_count > 1) {
			repeatChar = true;
			break;
		}
	}

//	cout << "Repeat: " << repeatChar << endl 
//		<< "Straight: " << straight << endl;

	return (repeatChar && straight);
}
