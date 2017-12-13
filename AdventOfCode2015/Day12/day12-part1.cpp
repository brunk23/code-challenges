#include<iostream>
#include<string>

using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	int count = 0,number;
	string input;
	bool isNeg = false;

	while( getline(cin, input) ) {
		number = 0;
		isNeg = false;
		for(int x=0; x!= input.size(); ++x) {
			if( input[x]>='0' && input[x]<='9' ) {
				number *= 10;
				int digit = input[x]-'0';
				if ( isNeg ) {
					number -= digit;
					
				} else {
					number += digit;
				}
			} else {
				if( input[x] =='-' ) {
					isNeg = true;
				} else {
					isNeg = false;
				}
				count += number;
				number = 0;
			}
		}
		count += number;
		cout << "Current count: " << count << endl;
	}

	cout << "The total was: " << count << endl;
	return 0;
}	
