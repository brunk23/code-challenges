#include <iostream>

#define MEMSIZE 10000

using namespace std;

/*
101 100 99  98  97  96  95  94  93  92  91
xxx 65  64  63  62  61  60  59  58  57  90
xxx 66  37  36  35  34  33  32  31  56  89
xxx 67  38  17  16  15  14  13  30  55  88
xxx 68  39  18   5   4   3  12  29  54  87
xxx 69  40  19   6   1   2  11  28  53  86
xxx 70  41  20   7   8   9  10  27  52  85
xxx 71  42  21  22  23  24  25  26  51  84
xxx 72  43  44  45  46  47  48  49  50  83
110 73  74  75  76  77  78  79  80  81  82
 */

/*
  Notes:
  * Bottom right corner (BRC) is (2n-1)^2
  * Bottom Left corner  (BLC) is BRC - (SL - 1)
  * Top Left Corner     (TLC) is BRC - 2(SL - 1)
  * Top Right Corner    (TRC) is BRC - 3(SL -1)
  * Side length         (SL) is (2n-1)

  Right side, directly left:  LOC - ( 8(n-2) + 1 )
  Top side, directly down:    LOC - ( 8(n-2) + 3 )
  Left side, directly right:  LOC - ( 8(n-2) + 5 )
  Bottom side, directly up:   LOC - ( 8(n-2) + 7 )

   R -> L   U -> D   L -> R  D -> U
   ------   ------   ------  ------
   n | c    n | c    n | c   n | c
   1 | -    1 | -    1 | -   1 | -
   2 | 1    2 | 3    2 | 5   2 | 7
   3 | 9    3 | 11   3 | 13  3 | 15
   4 | 17   4 | 19   4 | 21
   5 | 25   5 | 27   5 | 29
   6 | 33   6 | 35
 */

int BRC(int);
int BLC(int);
int TLC(int);
int TRC(int);
int SL(int);
int newsquares(int);
int abs(int);

int SL(int n) {
  return (2 * n - 1);
}

int BLC(int n) {
  return (BRC(n) - (SL(n) - 1 ));
}

int TLC(int n) {
  return (BRC(n) - 2 * (SL(n) -1 ));
}

int TRC(int n) {
  return (BRC(n) - 3 * (SL(n) -1 ));
}

int BRC(int n) {
  return SL(n)*SL(n);
}

int abs(int n) {
  if( n < 0 ) {
    return n * -1;
  }
  return n;
}

int newsquares( int length ) {
  return ( 4 * length + 4 );
}

enum dir{ RIGHT, UP, LEFT, DOWN};

int main() {
  int goal, tmp, a, b, c;
  int memory[MEMSIZE];
  int location, curr;
  // goal = 347991;
  
  cin >> goal;

  memory[1] = 1;
  curr = 1;
  
  for(location = 2; location < MEMSIZE; location++) {
    memory[location] = memory[location-1];

    /*
     * Bottom Right Corner
     */
    if( location > BRC(curr) ) {
      curr++;
      continue;
    }

    /*
     * Right side, no corner.
     */
    if( (location > BRC( curr -1 )) &&
	(location < TRC( curr )) ) {
      // Right side, no corner
      tmp = 8*(n-2) + 1;
      a = location - tmp;      // Left
      b = location - tmp - 1;  // Left Down
      c = location - tmp + 1;  // Left Up
      // This should always be safe, if we're
      // not adding the bottom right corner again.
      if( a < BRC( curr - 1 ) ) {
	memory[location] += memory[a];
      }
      // We sometimes have to add the bottom
      // right corner of the previous row.
      if( b == BRC( curr - 2 ) ) {
	memory[location] += memory[ BRC(curr-1) ];
      } else {
	memory[location] += memory[b];
      }
      // Can't add row not generated yet.
      if( a != TRC(curr -1) ) {
	memory[location] += memory[c];
      }
    }

    /*
     * Top Right Corner
     */

    /*
     * Top No Corners
     */

    /*
     * Top Left Corner
     */

    /*
     * Left No Corners
     */

    /*
     * Bottom Left Corner
     */

    /*
     * Bottom No Corners
     */
    
  }
  
  return 0;
}
