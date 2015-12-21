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
	string input;

	while( getline(cin, input) ) {
		for(unsigned int x = 0; x < input.size(); ++x) {
			if(input[x] == '(') {
				floors++;
			}
			if(input[x] == ')' ) {
				floors--;
			}
		}
	}
	cout << "We ended up on floor: " << floors << endl;
	return 0;
}


