#include <unistd.h>
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

#define MAX 100
#define COUNT 100

void create_next(const int current[MAX][MAX], int next[MAX][MAX]);
void read_data(int current[MAX][MAX]);
void print_array(const int current[MAX][MAX]);

int main()
{
  // We use two arrays and switch which one is current based on
  // the value of the number of seconds
  int even[MAX][MAX],
    odd[MAX][MAX],
    (*curr)[MAX]=even,
    (*next)[MAX]=odd,
    (*temp)[MAX]=0;
  int total = 0;
  
  // zero out arrays, just in case
  for(int i = 0; i < MAX; ++i) {
    for(int j = 0; j < MAX; ++j) {
      curr[i][j] = 0;
      next[i][j] = 0;
    }
  }
  
  read_data(even);

  for (int i = 0; i < COUNT; ++i) {
    print_array(curr);
    sleep(1);
    create_next(curr, next);
    temp = curr;
    curr = next;
    next = temp;
  }

  for(int i = 0; i < MAX; ++i) {
    for(int j = 0; j < MAX; ++j) {
      total += curr[i][j];
    }
  }

  cout << "There were " << total << " lights still on." << endl;

  return 0;
}

void print_array(const int current[MAX][MAX]) {
  cout << endl;
  for(int i = 0; i < MAX; ++i) {
    for(int j =0; j < MAX; ++j) {
      if( current[i][j] == 1 ) {
	cout << "#";
      } else {
	cout << ".";
      }
    }
    cout << endl;
  }
}

// This should create the next array
void create_next(const int current[MAX][MAX], int next[MAX][MAX])
{
  for(int i = 0; i < MAX; ++i) {
    for(int j = 0; j < MAX; ++j) {
      int total = 0;
      if( (i-1) >= 0) {
	total += current[i-1][j];
	if( (j-1) >= 0) {
	  total += current[i-1][j-1];
	}
	if( (j+1) < MAX ) {
	  total += current[i-1][j+1];
	}
      }
      if ( (j-1) >= 0 ) {
	total += current[i][j-1];
      }
      if ( (j+1) < MAX ) {
	total += current[i][j+1];
      }
      if( (i+1) < MAX ) {
	total += current[i+1][j];
	if( (j-1) >= 0) {
	  total += current[i+1][j-1];
	}
	if( (j+1) < MAX) {
	  total += current[i+1][j+1];
	}
      }
      if( total == 3 ) {
	next[i][j] = 1;
      } else {
	if( total == 2 && current[i][j] == 1 ) {
	  next[i][j] = 1;
	} else {
	  next[i][j] = 0;
	}
      }
    }
  }
}

void read_data(int current[MAX][MAX])
{
  string input;
  int x;

  x = 0;
  while( getline(cin, input) ) {
    for(unsigned int i = 0; i < input.size(); ++i) {
      if( i >= MAX || x >= MAX ) {
	cout << "ERROR: ARRAY TOO SMALL! PANIC" << endl;
	abort();
      }
      if( input[i] == '#' ) {
	current[x][i] = 1;
      } else {
	current[x][i] = 0;
      }
    }
    ++x;
  }
}
