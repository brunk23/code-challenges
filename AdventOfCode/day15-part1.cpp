#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::string;

// we don't know how big of a number we might need
typedef long score;

score mix_score(int itemcount, int *values, int *amount);

int main()
{
	// we will use two arrays
	// amount [   xx, xx, xx, xx, ...] how much of each ingredient
	// values [[  ca, ca, ca, ca, ...]
	//	   [  du, du, du, du, ...]
	//	   [  fl, fl, fl, fl, ...] etc.]
	// Then I can multiply amount[x] * values[n][x] 


	return 0;
}

