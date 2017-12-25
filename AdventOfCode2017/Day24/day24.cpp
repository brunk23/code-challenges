#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::stringstream;

#define PART2

class Used {
private:
  int *l;
  int max;

public:
  Used(int n) {
    int i;
    max = n;
    l = new int[n];
    for( i = 0; i < n; i++ ) {
      l[i] = 0;
    }
  };

  ~Used() {
    delete l;
  };

  Used(Used &a) {
    int i;
    l = new int[a.max];
    max = a.max;
    for( i = 0; i < a.max; i++ ) {
      l[i] = a.l[i];
    }
  };

  bool avail(int i) {
    if( l[i] == 0 ) {
      return true;
    }
    return false;
  };

  void use(int i) {
    l[i] = 1;
  };

  int mx() {
    return max;
  };
};

class Port {
private:
  int a;
  int b;
  
public:
  Port() {
    a = -1;
    b = -1;
  }
  
  Port(int x, int y) {
    a = x;
    b = y;
  }

  void assign(int x, int y) {
    a = x;
    b = y;
  }

  int hasNum(int n) {
    if( a == n ) {
      return b;
    }
    if( b == n ) {
      return a;
    }
    return -1;
  }
};

int makebridge(int y, int n, Port list[], Used u, int len) {
  static int mlen = 0;
  int x, count = 0, tmp, max;
  Used p(u);
  p.use(n);

  if( len > mlen ) {
    mlen = len;
  }
  
  x = list[n].hasNum(y);
  
  tmp = x + y;
  max = x + y;
  
  for(int i = 0; i < u.mx(); i++ ) {
    if( p.avail(i) ) {
      if( list[i].hasNum(x) > -1 ) {
	count++;
	tmp = x + y + makebridge(x,i,list,p,len+1);
	if( tmp > max ) {
	  max = tmp;
	}
      }
    }
  }
  
#ifdef PART2
  if( count == 0 ) {
    if( len < mlen ) {
      return -100;
    }
  }
#endif

  return max;
}

int main() {
  string input;
  unsigned int i, a, b, n = 0, tmp, total=0;
  Port list[100];
  
  while( getline(cin, input) ) {
    for( i = 0; i < input.length(); i++ ) {
      if( input[i] == '/' ) {
	input[i] = ' ';
	break;
      }
    }
    stringstream s(input);
    s >> a;
    s >> b;
    list[n].assign(a,b);
    n++;
  }

  Used u(n);

  for( i = 0; i < n; i++ ) {
    if( list[i].hasNum(0) > -1 ) {
      tmp = makebridge(0, i , list, u, 1);
      if( tmp > total ) {
	total = tmp;
      }
    }
  }
  
  cout << "The highest found was " << total << endl;
  return 0;
}
