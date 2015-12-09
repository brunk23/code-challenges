#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

const int CITIES = 10;

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


	return 0;
}
