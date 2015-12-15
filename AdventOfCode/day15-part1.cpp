#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::string;

// we don't know how big of a number we might need
typedef long score;

score mix_score(int spr, int but, int cho, int can);

int main()
{
	// There are 4 ingredients and 5 qualities
	int values[4][5];
	int amount[4];
	int spr, but, cho, can;
	score max, temp;;

	for( spr = 0; spr <= 100; ++spr ) {
	for( but = 0; but <= (100-spr); ++but ) {
	for( cho = 0; cho <= (100-spr-but); ++cho ) {
		temp = mix_score(spr, but, cho, (100-spr-but-cho));
		if ( temp > max ) {
			max = temp;
		}
	}}}	// end the for loops


	return 0;
}

score mix_score(int spr, int but, int cho, int can)
{
	int cap, dur, fla, tex, cal;
	
	cout << spr << " " << but << " " << cho << " " << can << endl;

	return 0;
}
