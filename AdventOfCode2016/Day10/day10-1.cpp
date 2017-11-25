#include <iostream>
#include <string>
#include "bot.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

Bot allBots[MAXBOTS];

int main(int argc, char *argv[]) {
  int bot, gives, high, low;
  string input;

  while( cin >> input ) {
    if( input[0] == 'b' ) {
      cin >> bot;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> gives;
      allBots[bot].setLow(bot,gives);
      //cout << "Bot " << bot << " low to " << gives << endl;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> gives;
      allBots[bot].setHigh(bot,gives);
      //cout << "Bot " << bot << " high to " << gives << endl;
      continue;
    }
    if( input[0] == 'v' ) {
      cin >> gives;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> bot;
      allBots[bot].gets(gives);
      //cout << "gave " << bot << ": " << gives << endl;
    }
  }

  bot = 0;
  while( true ) {
    if( allBots[bot].exists() ) {
      if( allBots[bot].hasBoth() ) {
	cout << bot << " has two chips" << endl;
	if( allBots[bot].winner() ) {
	  break;
	}
	high = allBots[bot].has(0);
	low = allBots[bot].has(1);
	if( low > high ) {
	  gives = high;
	  high = low;
	  low = gives;
	}
	allBots[ allBots[bot].highTo() ].gets(high);
	allBots[ allBots[bot].lowTo() ].gets(low);
	allBots[bot].reset();
      }
    }
    bot++;
    if( bot == MAXBOTS ) {
      bot = 0;
    }
  }
  
  /* if( (n == 61 && chips[0] == 17) ||
	(n == 17 && chips[0] == 61) ) {
      std::cerr << "I handle 61 and 17. My number is " << number << std::endl;
    }
    if( n > chips[0] ) {
      give( n, givesHighTo );
      give( chips[0], givesLowTo );
    } else {
      give( n, givesLowTo );
      give( chips[0], givesHighTo );
    }
  */
  return 0;
}
