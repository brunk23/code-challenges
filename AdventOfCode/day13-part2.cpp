#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>


using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;
using std::size_t;

const int NONE = 0;
const int PEOPLE = 10;
const int MYVAL = 0;

void read_input(string names[PEOPLE], int happiness[PEOPLE][PEOPLE]);
int which_person(string names[PEOPLE], string city);
void print_happiness_array(int dist[PEOPLE][PEOPLE], string [PEOPLE]);
int largest_happiness(const int possible[PEOPLE], const int full[PEOPLE][PEOPLE], int);
void print_small_array(const int possible[PEOPLE]);

int main()
{
	string names[PEOPLE];
	int happiness[PEOPLE][PEOPLE];
	int largest = INT_MIN;
	int temp;
	
	for(int x = 0; x < PEOPLE; x++) {
		for(int y = 0; y < PEOPLE; y++) {
			happiness[x][y] = NONE;
		}
		names[x] = "";
	}

	read_input(names, happiness);

	// print_happiness_array(happiness, names);

	// We seat everyone around ourself
	for(int x = 1; x < PEOPLE; ++x) {
		temp = largest_happiness(happiness[x],happiness, 0);
		if (temp > largest) {
			largest = temp;
		}
	}	
	cout << "The largest happiness was " << largest << endl;

	return 0;
}

/*
 * Will recursively call itself to find the longest happinesss
 */
int largest_happiness(const int possible[PEOPLE],
			const int full[PEOPLE][PEOPLE], int first)
{
	int largest = INT_MIN;
	int left[PEOPLE];
	int remaining = 0;

	// print_small_array(possible);

	// copy array into one we can modify
	for(int i = 0; i < PEOPLE; ++i) {
		if( ( possible[i] ) != NONE  ) {
			remaining++;
		}
	}

	// if we have one remaining, return it.
	if ( remaining < 2 ) {
		for(int i = 0; i < PEOPLE; ++i) {
			if( possible[i] != NONE ) {
				int a,b;
				a = possible[i];
				b = full[i][first];
				// cout << "Return [Last] a + b: " << a << 
				//	" + " << b << " = " << a+b << endl;
				return a+b;
			}
		}
	}

	// go through each possible partner, only checking ones with
	// a happiness != 0, and find the largest.
	for(int i = 0; i < PEOPLE; ++i) {
		if( possible[i] != NONE ) {
			if( first == -1 ) {
				first = i;
			}
			for(int j = 0; j < PEOPLE; ++j) {
				if( possible[j] != NONE ) {
					left[j] = full[i][j];
				} else {
					left[j] = NONE;
				}
			}
			remaining = possible[i];
			remaining += largest_happiness(left, full, first);			
			if( remaining > largest ) {
				largest = remaining;
			}
		}
	}
	// cout << "Return [sum]: " << largest << endl;
	return largest;
}

void print_small_array(const int possible[PEOPLE])
{
	for(int x = 0; x < PEOPLE; x++) {
		cout << "\t" << possible[x];
	}
	cout << endl;
}

/*
 * Print the array for debugging purposes
 */
void print_happiness_array(int dist[PEOPLE][PEOPLE], string names[PEOPLE]) {
	cout << "\t\t";
	for(int x = 0; x < PEOPLE; x++) {
		cout << names[x] << "\t";
	}
	cout << "\n";
	for(int x = 0; x < PEOPLE; x++) {
		cout << names[x] << "\t";
		for(int y = 0; y < PEOPLE; y++) {
			cout << "\t" << dist[x][y];
		}
		cout << endl;
	}
}

/*
 * Will read the input and populate both arrays as needed for the
 * problem description
 */
void read_input(string names[PEOPLE], int happiness[PEOPLE][PEOPLE]) {
	string input, name1, name2;
	int happy, n1_spot, n2_spot, negative;
	size_t start, len;
	
	names[0] = "Myself";
	happiness[0][0] = NONE;

	while( getline(cin, input) ) {
		happy = 0;
		start = 0;
		len = input.find(" would ");
		name1 = input.substr(start,len);
		start += len + 7;
		if( input[start] == 'g' ) {
			negative = 1;
		} else {
			negative = -1;	
		}
		start += 5;
		while ( input[start] >= '0' && input[start] <= '9') {
			happy *= 10;
			happy += input[start] - '0';
			start++;
		}	
		happy *= negative;
		start = input.find(" happiness units by sitting next to ");
		start += 36;
		len = input.size() - (start+1);
		name2 = input.substr(start,len);
	/*	
		cout << "name1: " << name1 << endl 
		     << "name2: " << name2 << endl
		     << "happiness : " << happy << endl;
	*/	 

		n1_spot = -1;
		n2_spot = -1;
		// We have parsed the input, now store it.
		n1_spot = which_person(names, name1);
		n2_spot = which_person(names, name2);

	/*
		for(int x = 0; x < PEOPLE; x++) {
			cout << x << ": " << names[x] << endl;
		}
	 */

		if ( !((n1_spot < 0) || (n2_spot < 0)) ) {
			happiness[n1_spot][n2_spot] += happy;
			happiness[n1_spot][0] = MYVAL;
			happiness[n2_spot][n1_spot] += happy;
			happiness[0][n1_spot] = MYVAL;
		} else {
			cout << "ERROR, NAME NOT FOUND\n";
		}
	}
}

/*
 * Will return the location of a person in the array and will
 * put a person in the array if one isn't there already
 */
int which_person(string names[PEOPLE], string person) {
	int spot = -1;
	for(int x = 0; x < PEOPLE; x++) {
		if(0 == names[x].compare(person)) {
			spot = x;
			break;
		}
		if(0 == names[x].compare("")) {
			spot = x;
			names[x] = person;
			break;
		}
	}	
	return spot;
}
