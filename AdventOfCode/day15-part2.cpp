#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::string;

// we don't know how big of a number we might need
typedef long score;

score mix_score(int spr, int but, int cho, int can, int values[4][5]);

int main()
{
	// There are 4 ingredients and 5 qualities
	// Hard coded to speed things up
	int values[4][5] = {	{2, 0, -2, 0, 3},
				{0, 5, -3, 0, 3},
				{0, 0, 5, -1, 8},
				{0, -1, 0, 5, 8}};
	// int amount[4];
	int spr, but, cho;
	score max=0, temp=0;

	for( spr = 0; spr <= 100; ++spr ) {
	for( but = 0; but <= (100-spr); ++but ) {
	for( cho = 0; cho <= (100-spr-but); ++cho ) {
		temp = mix_score(spr, but, cho, (100-spr-but-cho), values);
		if ( temp > max ) {
			max = temp;
		}
	}}}	// end the for loops

	cout << "The max score was: " << max << endl;

	return 0;
}

score mix_score(int spr, int but, int cho, int can, int values[4][5])
{
	int cap, dur, fla, tex, cal;
	score product;
	
	cap = values[0][0] * spr + values[1][0] * but + values[2][0] * cho
		+ values[3][0] * can;
	dur = values[0][1] * spr + values[1][1] * but + values[2][1] * cho
		+ values[3][1] * can;
	fla = values[0][2] * spr + values[1][2] * but + values[2][2] * cho
		+ values[3][2] * can;
	tex = values[0][3] * spr + values[1][3] * but + values[2][3] * cho
		+ values[3][3] * can;
	cal = values[0][4] * spr + values[1][4] * but + values[2][4] * cho
		+ values[3][4] * can;
	if( cap < 0 )
		cap = 0;
	if( dur < 0)
		dur = 0;
	if( fla < 0 )
		fla = 0;
	if( tex < 0 )
		tex = 0;
	if( cal != 500 )
		return 0;
	product = cap * dur * fla * tex;

	return product;
}
