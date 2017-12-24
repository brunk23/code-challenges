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

class Bridge {
public:
  int len;
  int str;

  Bridge(int ln, int sr) {
    len = ln;
    str = sr;
  }
  
  Bridge &operator=(const Bridge &o) {
    len = o.len;
    str = o.str;
    return *this;
  }
  
  Bridge &operator=(Bridge &o) {
    len = o.len;
    str = o.str;
    return *this;
  }
};

class Used {
private:
  int l[54];

public:
  Used() {
    int i;
    for( i = 0; i < 54; i++ ) {
      l[i] = 0;
    }
  }

  Used(Used &a) {
    int i;
    for( i = 0; i < 54; i++ ) {
      l[i] = a.l[i];
    }
  }

  bool avail(int i) {
    if( l[i] == 0 ) {
      return true;
    }
    return false;
  }

  void use(int i) {
    l[i] = 1;
  }
};

class Port {
private:
  int a;
  int b;
  bool used;
  
public:
  Port() {
    a = -1;
    b = -1;
    used = false;
  }
  
  Port(int x, int y) {
    a = x;
    b = y;
    used = false;
  }

  void assign(int x, int y) {
    a = x;
    b = y;
    used = false;
  }

  void reset() {
    used = false;
  }

  void use() {
    used = true;
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
  int x, count = 0, tmp, max;
  Used p(u);
  p.use(n);
  
  x = list[n].hasNum(y);
  
  tmp = x + y;
  max = x + y;
  
  for(int i = 0; i < 54; i++ ) {
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
  if( count == 0 ) {
    if( len < 30 ) {
      return -1000;
    }
  }
  return max;
}

int main() {
  string input;
  unsigned int i, a, b, n = 0, tmp, total=0;
  Port list[54];
  Used u;
  
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
