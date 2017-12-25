#include <iostream>

class Tape {
private:
  int *tp;
  int size;
  int offset;
  
public:
  Tape() {
    int i;
    size = 100;
    offset = 0;
    tp = new int[size];
    for( i = 0; i < size; i++ ) {
      tp[i] = 0;
    }
  };

  ~Tape() {
    int k;
    // std::cout << *this << std::endl;
    // std::cout << "The offset was " << offset << std::endl;
    // std::cout << "Tape length was " << size << std::endl;
    k = chksum();
    std::cout << "Checksum was " << k << std::endl;
    delete tp;
  };

  int chksum() {
    int i, j = 0;
    for( i = 0; i < size; i++ ) {
      j += tp[i];
    }
    return j;
  };
  
  void resize(int n) {
    int *tmp, i, *foo, j = 0;
    int inc = 100;
    if( n < 0 ) {
      offset += inc;
      j = inc;
    }
    size += inc;
    tmp = new int[size];

    for( i = 0; i < size; i++ ) {
      tmp[i] = 0;
    }
    
    for(i = 0; i < size - inc; i++) {
      tmp[ i + j] = tp[i];
    }
    foo = tp;
    tp = tmp;
    delete foo;
  };

  int getVal(int loc) {
    if( loc + offset < 0 ) {
      resize(-1);
    }
    if( loc + offset >= size ) {
      resize(1);
    }
    return tp[loc + offset];
  };

  void setVal(int loc, int val) {
    tp[loc + offset] = val;
  };

  friend std::ostream& operator<<(std::ostream &os, const Tape& s) {
    int i;
    for( i = 0; i < s.size; i++ ) {
      os << s.tp[i] << " ";
    }
    return os;
  };
};

enum States {a,b,c,d,e,f};

int main() {
  Tape t;
  int state = a, location = 0;
  long count = 0;
 
  while( count < 12172063) {
    count++;
    switch(state) {
    case a:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 1);
	location++;
	state = b;
      } else {
	t.setVal(location, 0);
	location--;
	state = c;
      }
      break;
    case b:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 1);
	location--;
	state = a;
      } else {
	t.setVal(location, 1);
	location--;
	state = d;
      }
      break;
    case c:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 1);
	location++;
	state = d;
      } else {
	t.setVal(location, 0);
	location++;
	state = c;
      }
      break;
    case d:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 0);
	location--;
	state = b;
      } else {
	t.setVal(location, 0);
	location++;
	state = e;
      }
      break;
    case e:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 1);
	location++;
	state = c;
      } else {
	t.setVal(location, 1);
	location--;
	state = f;
      }
      break;
    case f:
      if(t.getVal(location) == 0 ) {
	t.setVal(location, 1);
	location--;
	state = e;
      } else {
	t.setVal(location, 1);
	location++;
	state = a;
      }
      break;

    default:
      break;
    }
  }
  
  return 0;
}
