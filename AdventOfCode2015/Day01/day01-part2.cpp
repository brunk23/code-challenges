// let's do day 1, just so we have a complete set of code for the
// whole challenge

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

int main() {
	int floors = 0;
	int x = 0;
	string input;

	while( getline(cin, input) ) {
		for(; x < input.size(); ++x) {
			if(input[x] == '(') {
				floors++;
			}
			if(input[x] == ')' ) {
				floors--;
			}
			if( floors < 0 ) {
				break;
			}
		}
	}
	cout << "We went below the ground floor at character: " << (1+x) << endl;
	return 0;
}


