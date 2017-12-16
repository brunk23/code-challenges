#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::getline;
using std::string;
using std::stringstream;

struct PRG {
  char name;
  PRG *prev;
  PRG *next;
};

class Programs {
  int length;
  PRG *head;
  PRG *tail;
  
public:
  Programs(int number) {
    int i = 0;
    char n = 'a';
    PRG *curr = 0, *tmp;
    head = 0;
    tail = 0;
    tmp = 0;
    length = number;
    
    while( i < number ) {
      tmp = new PRG;

      tmp->name = n;
      n++;
      tmp->prev = 0;
      tmp->next = 0;
      
      if( head == 0 ) {
	head = tmp;
	curr = tmp;
      } else {
	curr->next = tmp;
	tmp->prev = curr;
	curr = tmp;
      }
      i++;
    }
    tail = tmp;
  }

  void partner(char a, char b) {
    int i, p = 0, q = 0;
    PRG *curr = head;
    
    for( i = 0; i < length; i++ ) {
      if( curr->name == a ) {
	p = i;
      }
      if( curr->name == b ) {
	q = i;
      }
      curr = curr->next;
    }
    exchange(p,q);
  }
  
  /*
   * Exchange was a little tricky.
   */
  void exchange(int a, int b) {
    int i;
    PRG *aspot = 0;
    PRG *bspot = 0;
    PRG *tmp = head;
    
    for(i = 0; i < length; i++ ) {
      if( i == a ) {
	aspot = tmp;
      }
      if( i == b ) {
	bspot = tmp;
      }
      tmp = tmp->next;
    }
    // fails when swapping 1,0
    if(aspot->prev) {
      aspot->prev->next = bspot;
    } else {
      head = bspot;
    }
    if(aspot->next) {
      aspot->next->prev = bspot;
    } else {
      tail = bspot;
    }
    if(bspot->prev) {
      bspot->prev->next = aspot;
    } else {
      head = aspot;
    }
    if(bspot->next) {
      bspot->next->prev = aspot;
    } else {
      tail = aspot;
    }
    
    tmp = aspot->prev;
    aspot->prev = bspot->prev;
    bspot->prev = tmp;
    tmp = aspot->next;
    aspot->next = bspot->next;
    bspot->next = tmp;
  }

  /*
   * Implement the spin
   */
  void spin(int n) {
    int i = 1;
    PRG *curr = tail;
    
    while( i != n ) {
      curr = curr->prev;
      i++;
    }

    tail->next = head;
    head->prev = tail;
    head = curr;
    tail = curr->prev;
    head->prev = 0;
    tail->next = 0;
  }
  
  char getName(int n) {
    int i = 0;
    PRG *curr = head;
    while( i != n ) {
      curr = curr->next;
      i++;
    }
    if( n > 0 && n < length-1 ) {
      if( curr->prev == 0 || curr->next == 0 ) {
	return '#';
      }
    }
    return curr->name;
  }

  int getlen() {
    return length;
  }
  
};

void process(Programs &);
void printall(Programs &);

void printall(Programs &a) {
  int i;

  for( i = 0; i < a.getlen(); i++ ) {
    cout << a.getName(i) << "  ";
  }
  cout << endl;
}

void process(Programs &prog) {
  string input;

  int a, b;
  char p, q;
  
  while( getline(cin, input) ) {
    for(unsigned int i = 0; i < input.length(); i++ ) {
      printall(prog);
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
	prog.exchange(a,b);
	continue;
      }
      if( input[i] == 'p' ) {
	i++;
	p = input[i];
	i += 2;
	q = input[i];
	prog.partner(p,q);
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
	prog.spin(a);
	continue;
      }
    } 
  }
}

int main() {
  static int NUMBER = 16;
  Programs a( NUMBER );

  //process(a);

  printall(a);
  a.exchange(1,0);
  printall(a);
  a.exchange(0,1);
  printall(a);
  
  return 0;
}
