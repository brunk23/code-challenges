#include <iostream>
#include <string>

using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	string input;
	while( getline(cin, input) ) {
		cout << input.size() << endl;
	}
	return 0;
}
