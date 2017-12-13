#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::getline;
using std::string;
using std::stringstream;

class Layer {
private:
  int depth;
  int length;
  Layer *next;

public:
  Layer() {
    depth = 0;
    length = 0;
  }

  Layer(int d, int l) {
    depth = d;
    length = l;
    next = 0;
  }

  void addNext(Layer *n) {
    next = n;
  }

  Layer *getNext() {
    return next;
  }

  int getDepth() {
    return depth;
  }

  int cost(int t) {
    int n = t % (( length - 1 ) * 2);
    if( n == 0 ) {
      return 1;   // Any cost is too high.
    }
    return 0;
  }

};

Layer *readInput();
int gcd(int, int);
int lcm(int, int);
int cost(Layer *, int);

int gcd(int a, int b) {
  int t;
  if( (a<1) || (b<1) ) {
    return 1;
  }
  while( b != 1 ) {
    t = a % b;
    if( 0 == t ) {
      return b;
    }
    a = b;
    b = t;
  }
  return 1;
}
 
int lcm(int a, int b) {
  int t = gcd(a,b);
  return (a*b)/t;
}  

Layer *readInput() {
  int i, dep, len;
  Layer *head = 0;
  Layer *curr = 0;
  string input;

  while( getline(cin, input) ) {
    for(i = 0; i < input.length(); i++ ) {
      if( input[i] == ':' ) {
	input[i] = ' ';
      }
    }
    stringstream s(input);
    if( !(s >> dep) || !(s >> len) ) {
      cerr << "ERROR: " << input << endl;
      return 0;
    }
    if( 0 == head ) {
      head = new Layer(dep, len);
      curr = head;
    } else {
      curr->addNext(new Layer(dep, len));
      curr = curr->getNext();
    }
  }
  return head;
}

int cost(Layer *head, int t) {
  int i = 0;
  int cost = 0;
  Layer *curr = head;
  while(curr) {
    if( i > curr->getDepth() ) {
      curr = curr->getNext();
      continue;
    }
    if( i == curr->getDepth() ) {
      cost += curr->cost(i + t);
      if( cost > 0 ) {
	return cost;
      }
    }
    i++;
  }
  return cost;
}

int main() {
  string input;
  Layer *head = 0;
  int i = 0;
  head = readInput();

  while( cost(head, i) > 0 ) {
    i++;
  }

  cout << "It is safe after " << i << " picoseconds." << endl;
  return 0;
}
