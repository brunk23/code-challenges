#include <iostream>
#include <string>

#define MAX 8

void swappos(int, int);
void swaplet(char, char);
void rotr(int);
void rotl(int);
void reverse(int,int);
void rotlet(char);
void move(int,int);
void inswap();
void inrotate();
void inreverse();
void inmove();

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;

char passcode[MAX+1] = {'a', 'b', 'c', 'd',
		    'e', 'f', 'g', 'h', 0};

void move(int x, int y) {
  int i,j;
  char n, tmp[MAX];
  if( (x >= MAX) || ( y >= MAX) ) {
    cerr << "ERROR: OUT OF RANGE move(" << x
	 << "," << y << ");" << endl;
    return;
  }
  n = passcode[x];
  j=0;
  for(i=0; i<MAX; i++) {
    if( i == x ) {
      j++;
    }
    tmp[i] = passcode[j];
    j++;
  }
  j=0;
  for(i = 0; i < MAX; i++) {
    if( i == y ) {
      passcode[i] = n;
    } else {
      passcode[i] = tmp[j];
      j++;
    }
  }
}

void reverse(int x, int y) {
  char n;
  if( (x >= MAX) || ( y >= MAX) ) {
    cerr << "ERROR: OUT OF RANGE reverse(" << x
	 << "," << y << ");" << endl;
    return;
  }
  if( x > y ) {
    x = x^y;
    y = x^y;
    x = x^y;
  }
  while( y > x ) {
    n = passcode[x];
    passcode[x] = passcode[y];
    passcode[y] = n;
    x++;
    y--;
  }
}

void rotr(int count) {
  int i,j;
  for( i = 0; i < count; i++) {
    for( j = MAX; j > 0; j--) {
      passcode[j] = passcode[j-1];
    }
    passcode[0] = passcode[MAX];
    passcode[MAX] = 0;
  }
}

void rotl(int count) {
  int i,j;
  for( i = 0; i < count; i++) {
    passcode[MAX] = passcode[0];
    for(j = 0; j < MAX; j++) {
      passcode[j] = passcode[j+1];
    }
    passcode[MAX] = 0;
  }
}

void rotlet(char n) {
  int i;
  for(i = 0; i < MAX; i++) {
    if( passcode[i] == n ) {
      break;
    }
  }
  if( i >= 4 ) {
    i++;
  }
  rotr(i+1);
}
 

void swaplet(char a, char b) {
  int i;
  for( i = 0; i < MAX; i++ ) {
    if( passcode[i] == a ) {
      passcode[i] = b;
      continue;
    }
    if( passcode[i] == b ) {
      passcode[i] = a;
    }
  }
}

void swappos(int x, int y) {
  char n;
  if( (x >= MAX) || ( y >= MAX) ) {
    cerr << "ERROR: OUT OF RANGE swap(" << x
	 << "," << y << ");" << endl;
    return;
  }
  n = passcode[x];
  passcode[x] = passcode[y];
  passcode[y] = n;
}

void inswap() {
  string foo;
  int x, y;
  char a, b;

  cin >> foo;
  if( foo[0] == 'p' ) {
    cin >> x;
    cin >> foo;
    cin >> foo;
    cin >> y;
    swappos(x,y);
  } else {
    cin >> a;
    cin >> foo;
    cin >> foo;
    cin >> b;
    swaplet(a,b);
  }
}

void inrotate() {
  string foo;
  char a;
  int x;

  cin >> foo;
  if( foo[0]=='l' ) {
    cin >> x;
    cin >> foo;
    rotl(x);
    return;
  }
  if( foo[0] == 'r' ) {
    cin >> x;
    cin >> foo;
    rotr(x);
    return;
  }
  cin >> foo;
  cin >> foo;
  cin >> foo;
  cin >> foo;
  cin >> a;
  rotlet(a);
}

void inreverse() {
  string foo;
  int x, y;

  cin >> foo;
  cin >> x;
  cin >> foo;
  cin >> y;
  reverse(x,y);
}

void inmove() {
  string foo;
  int x,y;

  cin >> foo;
  cin >> x;
  cin >> foo;
  cin >> foo;
  cin >> y;
  move(x,y);
}

int main() {
  string foo;

  while ( cin >> foo ) {
    if( foo[0]=='s' ) {
      inswap();
      continue;
    }
    if( foo[2]=='t' ) {
      inrotate();
      continue;
    }
    if( foo[0]=='r' ) {
      inreverse();
      continue;
    }
    inmove();
  }

  cout << passcode << endl;
  
  return 0;
}
