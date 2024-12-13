#include <stdio.h>

/***
_ + _ * _^2 + _^3 - _ = 399

red coin = 2
concave coin = 7
corroded coin = triangle (3?)
blue coin = 9
shiny coin = pentagon (5)

* 9 - 2 - 5 - 7 - 3 *
***/

int main() {
	int coins[] = { 2, 3, 5, 7, 9 };
	int a,b,c,d,e,f;

	for( a = 0; a < 5; ++a ) {
	for( b = 0; b < 5; ++b ) {
	for( c = 0; c < 5; ++c ) {
	for( d = 0; d < 5; ++d ) {
	for( e = 0; e < 5; ++e ) {
		if(value(coins[a],coins[b],coins[c],
			coins[d],coins[e],coins[f]) == 399 ) {
			printf("%i, %i, %i, %i, %i\n",
				a,b,c,d,e);
		}
	}}}}}

return 0;

}

int value(int a, int b, int c, int d, int e) {
	int temp;
	temp = d * d * d;
	temp += c * c * b;
	temp += a;
	temp -= e;

	return temp;
}
