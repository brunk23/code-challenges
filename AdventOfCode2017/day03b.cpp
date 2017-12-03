#include <iostream>

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

int newsquares(int);
int abs(int);

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
  int goal;
  int s, e, len, mid, direction = RIGHT;
  s = e = len =1;
  // goal = 347991;

  cin >> goal;

  while( e < goal ) {
    s = e +1;
    e += newsquares(len);
    len += 2;
  }
  cout << "Length: " << len << "\tMin: " << s
       << "\tMax: " << e << endl;
  // Where is goal
  mid = len/2;
  cout << mid + abs(((goal-s)%(len-1))+1-mid) << endl;
  
  return 0;
}
