#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::getline;
using std::string;

class Programs {
private:
  int length;
  int *list;

  void rot() {
    int i, tmp;

    tmp = list[length - 1];
    for( i = length - 2; i >= 0; i-- ) {
      list[i+1] = list[i];
    }
    list[0] = tmp;
  }
  
public:
  Programs(int number) {
    int i = 0;
    char n = 'a';
    length = number;

    list = new int[number];

    while( i < number ) {
      list[i] = n;
      n++;
      i++;
    }
  }

  bool isRestart() {
    int i;
    for( i = 0; i < length; i++ ) {
      if(list[i] != ('a' + i)) {
	return false;
      }
    }
    return true;
  }
  
  void partner(char a, char b) {
    int i, p = 0, q = 0;
 
    for( i = 0; i < length; i++ ) {
      if( list[i] == a ) {
	p = i;
      }
      if( list[i] == b ) {
	q = i;
      }
    }
    exchange(p,q);
  }
  
  /*
   * Exchange was a little tricky.
   */
  void exchange(int a, int b) {
    int tmp;

    if( b == a ) {
      return;
    }

    tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
  }

  /*
   * Implement the spin
   */
  void spin(int n) {
    int i;

    for( i = 0; i < n; i++ ) {
      rot();
    }
  }
  
  int getlen() {
    return length;
  }

  friend std::ostream &operator<<(std::ostream &os, const Programs &a) {
    int i;
    for( i = 0; i < a.length; i++ ) {
      os << static_cast<char>(a.list[i]);
    }
    return os;
  }
  
};

struct Demand {
  char opt;
  int v1;
  int v2;
  char c1;
  char c2;
  Demand *next;
};
  
class Command {
private:
  Demand *head;
  Demand *tail;

  void attach(Demand *tmp) {
    if( head == 0 ) {
      head = tmp;
      tail = tmp;
      return;
    }
    tail->next = tmp;
    tail = tmp;
  }
  
public:
  Command() {
    head = 0;
    tail = 0;
  }

  void add(int n) {
    Demand *tmp = new Demand;

    tmp->opt = 's';

    tmp->v1 = n;
    tmp->v2 = -1;

    tmp->c1 = '#';
    tmp->c2 = '#';

    tmp->next = 0;
    attach(tmp);
  }

  void add(int n, int p) {
    Demand *tmp = new Demand;

    tmp->opt = 'x';

    tmp->v1 = n;
    tmp->v2 = p;

    tmp->c1 = '#';
    tmp->c2 = '#';

    tmp->next = 0;

    attach(tmp);
  }

  void add(char n, char p) {
    Demand *tmp = new Demand;

    tmp->opt = 'p';

    tmp->v1 = -1;
    tmp->v2 = -1;

    tmp->c1 = n;
    tmp->c2 = p;

    tmp->next = 0;

    attach(tmp);
  }

  void run(Programs &p) {
    Demand *curr = head;

    while(curr) {
      switch( curr->opt ) {
      case 'x':
	p.exchange(curr->v1, curr->v2);
	break;
      case 's':
	p.spin(curr->v1);
	break;
      case 'p':
	p.partner(curr->c1, curr->c2);
	break;
      default:
	cerr << "Command not found" << endl;
	return;
      }
      curr = curr->next;
    }
  }
};

void process(Programs &);

void process(Programs &prog) {
  string input;
  Command commands;
  unsigned int i;
  int a, b;
  char p, q;
  
  while( getline(cin, input) ) {
    for(i = 0; i < input.length(); i++ ) {
      if(input[i] == 'x' ) {
	i++;
	a = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  a *= 10;
	  a += input[i] - '0';
	  i++;
	}
	i++;
	b = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  b *= 10;
	  b += input[i] -'0';
	  i++;
	}
 
	commands.add(a,b);
	continue;
      }
      if( input[i] == 'p' ) {
	i++;
	p = input[i];
	i += 2;
	q = input[i];
	commands.add(p,q);
	continue;
      }
      if( input[i] == 's' ) {
	i++;
	a = 0;
	while( input[i] >= '0' && input[i] <= '9' ) {
	  a *= 10;
	  a += input[i] - '0';
	  i++;
	}
	commands.add(a);
	continue;
      }
    }
  }

  for( i = 0; i < 1000000000; i++ ) {
    commands.run(prog);
    if( prog.isRestart() ) {
      cout << "We repeat at " << i+1 << " steps so we only need "
	   << 1000000000 % (i+1) << " iterations." << endl;
      break;
    }
  }
  a = 1000000000 % (i+1);
  for( b = 0; b < a; b++ ) {
    commands.run(prog);
    if( b == 0 ) {
      cout << b+1 << ": " << prog << endl;
    }
  }
  cout << b << ": " << prog << endl;
}

int main() {
  static int NUMBER = 16;
  Programs a( NUMBER );

  process(a);

  return 0;
}
