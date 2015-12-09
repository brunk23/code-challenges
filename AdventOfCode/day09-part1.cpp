#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::size_t;
using std::stoi;

const int CITIES = 10;

void read_input(string names[CITIES], int distance[CITIES][CITIES]);
int which_city(string names[CITIES], string city);
void print_distance_array(int dist[CITIES][CITIES]);

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

	print_distance_array(distance);


	return 0;
}

/*
 * Print the array for debugging purposes
 */
void print_distance_array(int dist[CITIES][CITIES]) {
	for(int x = 0; x < CITIES; x++) {
		for(int y = 0; y < CITIES; y++) {
			cout << "\t" << dist[x][y];
		}
		cout << endl;
	}
}
enum TOKEN {
	FIRST,
	SECOND
};

/*
 * Will read the input and populate both arrays as needed for the
 * problem description
 */
void read_input(string names[CITIES], int distance[CITIES][CITIES]) {
	string input, name1, name2;
	int dist, n1_spot, n2_spot;
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
		start += len + 3;
		dist = stoi(input.substr(start));

	/*
		cout << input << endl;
		cout << "name1: " << name1 << endl 
		     << "name2: " << name2 << endl
		     << "dist : " << dist << endl;
	 */

		n1_spot = -1;
		n2_spot = -1;
		// We have parsed the input, now store it.
		n1_spot = which_city(names, name1);
		n2_spot = which_city(names, name2);

	/*
		for(int x = 0; x < CITIES; x++) {
			cout << x << ": " << names[x] << endl;
		}
	 */
		if ( !((n1_spot < 0) || (n2_spot < 0)) ) {
			distance[n1_spot][n2_spot] = dist;
			distance[n2_spot][n1_spot] = dist;
		} else {
			cout << "ERROR, NAME NOT FOUND\n";
		}
	}
}

/*
 * Will return the location of a city in the array and will
 * put a city in the array if one isn't there already
 */
int which_city(string names[CITIES], string city) {
	int spot = -1;
	for(int x = 0; x < CITIES; x++) {
		if(0 == names[x].compare(city)) {
			spot = x;
			break;
		}
		if(0 == names[x].compare("")) {
			spot = x;
			names[x] = city;
			break;
		}
	}	
	return spot;
}
