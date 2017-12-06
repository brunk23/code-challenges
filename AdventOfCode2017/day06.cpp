#include <iostream>

#define LENGTH 16

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

struct State {
  int arr[LENGTH];
  struct State *next;
};

bool addState(int a[LENGTH], State *states);
void nextState(int a[LENGTH]);
void getNumbers(int a[LENGTH]);
void createState(int a[LENGTH], State *s);
void printArray(int a[LENGTH]);

void printArray(int a[LENGTH]) {
  int i;
  for( i = 0; i < LENGTH; i++ ) {
    cout << a[i] << "  ";
  }
  cout << endl;
}

void createState(int a[LENGTH], State *s) {
  int i;
  s->next = 0;
  for( i = 0; i < LENGTH; i++ ) {
    s->arr[i] = a[i];
  }
}

/*
 * Returns true if the state was added, false
 * if the state was not added (because it matched
 * a previous state.   UNDONE
 */
bool addState(int a[LENGTH], State *states) {
  State *curr = new State;
  State *list = states;
  int i;

  createState(a, curr);

  while( list ) {
    for( i = 0; i < LENGTH; i++ ) {
      if( list->arr[i] !=a[i] ) {
	break;
      }
    }
    if( i == LENGTH ) {
      return false;
    }
    list = list->next;
  }

  list = states;
  while( list->next ) {
    list = list->next;
  }
  list->next = curr;

  return true;
}



/*
 * Distributes the largest number over
 * the array
 */
void nextState(int a[LENGTH]) {
  int i, largest, loc;

  largest = a[0];
  loc = 0;

  for( i = 0; i < LENGTH; i++ ) {
    if( a[i] > largest ) {
      loc = i;
      largest = a[i];
    }
  }

  a[loc] = 0;

  for( i = 1; i <= largest; i++ ) {
    a[ (i + loc) % LENGTH ]++;
  } 
}

void getNumbers(int a[LENGTH]) {
  int i = 0, x;
  while( cin >> x ) {
    if( i == LENGTH ) {
      cerr << "TOO MANY NUMBERS" << endl;
      return;
    }
    a[i] = x;
    i++;
  }
}

int main() {
  int a[LENGTH], steps = 0,i;
  State *first = new State;
  State final;

  getNumbers(a);
  createState(a, first);

  do {
    nextState(a);
    steps++;
  } while( addState(a, first) );

  printArray(a);

  /*
   * Part a
   */
  cout << "It took " << steps << " steps" << endl;

  /*
   * Part b
   */
  steps = 0;
  createState(a, &final);
  while( steps < 100000 ) {
    nextState(a);
    steps++;
    for( i = 0; i < LENGTH; i++ ) {
      if( a[i] != final.arr[i] ) {
	break;
      }
    }
    if( i == LENGTH ) {
      break;
    }
  }
  cout << "The loop is " << steps << " long." << endl;

  return 0;
}
