#include <iostream>
#include <string>

using std::getline;
using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
	size_t location;
	int value = 0;
	string input;
	bool possible = true;

	while( getline(cin, input) ) {
		if( (location = input.find("children: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 3 ) {
				continue;
			}
		}

		if( (location = input.find("cats: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value <= 7 ) {
				continue;
			}
		}

		if( (location = input.find("samoyeds: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 2 ) {
				continue;
			}
		}

		if( (location = input.find("pomeranians: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value >= 3 ) {
				continue;
			}
		}

		if( (location = input.find("akitas: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 0 ) {
				continue;
			}
		}

		if( (location = input.find("vizslas: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 0 ) {
				continue;
			}
		}

		if( (location = input.find("goldfish: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value >= 5 ) {
				continue;
			}
		}

		if( (location = input.find("trees: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value <= 3 ) {
				continue;
			}
		}

		if( (location = input.find("cars: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 2 ) {
				continue;
			}
		}

		if( (location = input.find("perfumes: ")) != std::string::npos) {
			value = 0;
			for(unsigned int x = location; x < input.size(); ++x) {
				if(input[x] == ',') {
					break;
				}
				if(input[x] >= '0' && input[x] <= '9') {
					value *= 10;
					value += input[x] - '0';
				}
			}
			if( value != 1 ) {
				continue;
			}
		}

		// This Sue could qualify
		cout << input << endl;

	}

	return 0;
}
