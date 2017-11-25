#include <iostream>
#include <string>
#include "bot.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

Bot allBots[MAXBOTS];
int output[20];

int main(int argc, char *argv[]) {
  int bot, gives, high, low;
  string input;
  bool running;
  
  for( bot = 0; bot < 20; bot++ ) {
    output[bot] = 0;
  }
  
  while( cin >> input ) {
    if( input[0] == 'b' ) {
      cin >> bot;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> gives;
      if( input[0] == 'b' ) {
	allBots[bot].setLow(bot,gives);
      } else {
	allBots[bot].setLow(bot,(-1 * gives)-1);
      }
      //cout << "Bot " << bot << " low to " << gives << endl;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> input;
      cin >> gives;
      if( input[0] == 'b' ) {
	allBots[bot].setHigh(bot,gives);
      } else {
	allBots[bot].setHigh(bot,(-1 * gives)-1);
      }
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
  running = false;
  while( true ) {
    if( allBots[bot].exists() ) {
      if( allBots[bot].hasBoth() ) {
	allBots[bot].winner();
	running = true;
	high = allBots[bot].has(0);
	low = allBots[bot].has(1);
	if( low > high ) {
	  gives = high;
	  high = low;
	  low = gives;
	}
	if( allBots[bot].highTo() >= 0 ) {
	  allBots[ allBots[bot].highTo() ].gets(high);
	} else {
	  output[ (allBots[bot].highTo()+1) * -1 ] = high;
	}
	if( allBots[bot].lowTo() >= 0 ) {
	  allBots[ allBots[bot].lowTo() ].gets(low);
	} else {
	  output[ (allBots[bot].lowTo()+1) * -1 ] = low;
	}
	allBots[bot].reset();
      }
    }
    bot++;
    if( bot == MAXBOTS ) {
      if( running ) {
	running = false;
	bot = 0;
      } else {
	break;
      }
    }
  }

  cout << "The sum of outputs 0, 1, and 2 is "
       << (output[0] * output[1] * output[2]) << endl;

  return 0;
}
