#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::size_t;

const int CITIES = 10;

void read_input(string names[CITIES], int distance[CITIES][CITIES]);

int main()
{
	string names[CITIES];
	int distance[CITIES][CITIES];
	
	for(int x = 0; x < CITIES; x++) {
		for(int y = 0; y < CITIES; y++) {
			distance[x][y] = 0;
		}
		names[x] = "";
	}

	read_input(names, distance);


	return 0;
}

enum TOKEN {
	FIRST,
	SECOND
};

void read_input(string names[CITIES], int distance[CITIES][CITIES]) {
	string input, name1, name2;
	TOKEN location = FIRST;
	size_t start, len;

	while( getline(cin, input) ) {
		start = 0;
		len = input.find(" to ");
		name1 = input.substr(start,len);
		start += len + 4;
		len = input.find(" = ");
		len -= start;
		name2 = input.substr(start,len);
		start += len + 4;
		cout << input << endl;
		cout << "name1: " << name1 << endl 
		     << "name2: " << name2 << endl;
	}

}
