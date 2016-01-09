#include <iostream>
#include <cstdlib>
#include <iomanip>

/* Trying to do this monte-carlo doesn't work
 * quickly enough to get the right precision.
 * So, I need to find a better way.
 */

int main()
{
  int player1 = 0;
  int player2 = 0;
  int p1wins = 0;
  int p2wins = 0;
  int total;

  std::cout << std::setprecision(11);
  
  while( true ) {
    total = 0;

    while (total < 1000000) {
      player1 = rand() % 1000000;
      total += player1;
    }
    while (total < 2000000) {
      player2 = rand() % 1000000;
      total += player2;
    }
    if( player1 > player2 ) {
      p1wins++;
    }
    if( player2 > player1 ) {
      p2wins++;
    }
    if( (p1wins+p2wins)%1000 == 0 ) {
      std::cout << "Player 2 wins: "
		<< (static_cast< double >( p2wins )/(p2wins+p1wins))
		<< "\n";
    }
  }
  return 0;
}
