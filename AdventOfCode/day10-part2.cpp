#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>


using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	int count = 0;
	string input = "1321131112";
	string next = "";
	char count_c;
	char current = '\0';
	
	for (int i = 0; i < 50; ++i ) {
		next = "";	
		count = 0;
		for ( unsigned int x = 0; x < input.size(); x++) {

			if( current == input[x] ) {
				count++;
			} else {
				if( current && count ) {
					// We can tighten this up because count is
					// limited to 1, 2, or 3 according to the wikipedia
					// pages on the Look-and-say sequence
					if(count == 1) {
						count_c = '1';
					} else {
					if(count == 2) {
						count_c = '2';
					} else {
					if(count == 3) {
						count_c = '3';
					} else {
						cout << "ERROR";
					}}}	 // Terminate the nested if blocks
					next = next + count_c + current;
				}
				current = input[x];
				count = 1;
			}
		}
		if(count == 1) {
			count_c = '1';
		} else {
		if(count == 2) {
			count_c = '2';
		} else {
		if(count == 3) {
			count_c = '3';
		} else {
			cout << "ERROR";
		}}}	 // Terminate the nested if blocks
		next = next + count_c + current;
		input = next;	
			// cout << i << ": " << input << endl;
		cout << i << ": " << input.size() << endl;
	}
	
	cout << next.size() << endl;


	return 0;
}
