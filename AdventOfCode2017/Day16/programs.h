#ifndef PROGRAMS_H
#define PROGRAMS_H

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

#endif
