#include <iostream>
#include <string>

#define MAX 8

void swappos(int, int, char []);
void swaplet(char, char, char []);
void rotr(int, char []);
void rotl(int, char []);
void reverse(int,int, char []);
void rotlet(char, char []);
void move(int,int, char []);
void inswap(char []);
void inrotate(char []);
void inreverse(char []);
void inmove(char []);
void rotlethelper(char, char []);
void cpy(char [], char []);

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;


// DONE
void move(int x, int y, char passcode[]) {
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

// DONE
void reverse(int x, int y, char passcode[]) {
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

// DONE
void rotl(int count, char passcode[]) {
  int i,j;
  for( i = 0; i < count; i++) {
    for( j = MAX; j > 0; j--) {
      passcode[j] = passcode[j-1];
    }
    passcode[0] = passcode[MAX];
    passcode[MAX] = 0;
  }
}

// DONE
void rotr(int count, char passcode[]) {
  int i,j;
  for( i = 0; i < count; i++) {
    passcode[MAX] = passcode[0];
    for(j = 0; j < MAX; j++) {
      passcode[j] = passcode[j+1];
    }
    passcode[MAX] = 0;
  }
}

// XXX FIND WAY TO UNDO
void rotlethelper(char n, char passcode[]) {
  int i;
  for(i = 0; i < MAX; i++) {
    if( passcode[i] == n ) {
      break;
    }
  }
  if( i >= 4 ) {
    i++;
  }
  rotl(i+1,passcode);
}

// copy a into b
void cpy(char a[], char b[]) {
  int i;
  for( i = 0; i < MAX+1; i++ ) {
    b[i] = a[i];
  }
}

// DONE
void rotlet(char n, char passcode[]) {
  char a[MAX+1];
  int i;
  for( i = 0; i < MAX; i++ ) {
    cpy(passcode, a);
    rotr(i,a);
    rotlethelper(n, a);
    if( a[0] == passcode[0] ) {
      rotr(i,passcode);
      return;
    }
  }
}

// DONE
void swaplet(char a, char b, char passcode[]) {
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

// DONE
void swappos(int x, int y, char passcode[]) {
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

// DONE
void inswap(char passcode[]) {
  string foo;
  int x, y;
  char a, b;

  cin >> foo;
  if( foo[0] == 'p' ) {
    cin >> x;
    cin >> foo;
    cin >> foo;
    cin >> y;
    swappos(x,y,passcode);
  } else {
    cin >> a;
    cin >> foo;
    cin >> foo;
    cin >> b;
    swaplet(a,b,passcode);
  }
}

void inrotate(char passcode[]) {
  string foo;
  char a;
  int x;

  cin >> foo;
  if( foo[0]=='l' ) {
    cin >> x;
    cin >> foo;
    rotl(x, passcode);
    return;
  }
  if( foo[0] == 'r' ) {
    cin >> x;
    cin >> foo;
    rotr(x, passcode);
    return;
  }
  cin >> foo;
  cin >> foo;
  cin >> foo;
  cin >> foo;
  cin >> a;
  rotlet(a, passcode);
}

void inreverse(char passcode[]) {
  string foo;
  int x, y;

  cin >> foo;
  cin >> x;
  cin >> foo;
  cin >> y;
  reverse(x,y,passcode);
}

void inmove(char passcode[]) {
  string foo;
  int x,y;

  cin >> foo;
  cin >> x;
  cin >> foo;
  cin >> foo;
  cin >> y;
  move(y,x,passcode);
}

int main() {
  string foo;
  // f b g d c e a h
  char passcode[MAX+1] = {'f', 'b', 'g', 'd',
			  'c', 'e', 'a', 'h', 0};


  while ( cin >> foo ) {
    if( foo[0]=='s' ) {
      inswap(passcode);
      continue;
    }
    if( foo[2]=='t' ) {
      inrotate(passcode);
      continue;
    }
    if( foo[0]=='r' ) {
      inreverse(passcode);
      continue;
    }
    inmove(passcode);
  }

  cout << passcode << endl;
  
  return 0;
}
