#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::getline;

const int GOAL = 150;
const int MAX = 20;

int working_combo(int numbers[MAX],int current[MAX], int count, int min);
int find_min(int numbers[MAX],int current[MAX], int count, int min);
int inc_array(int current[MAX], int count);

int main()
{
  int numbers[MAX], current[MAX], input=0, x=0, y=0, total=0, min=MAX;

  // initialize the array to 0s
  for(x = 0; x < MAX; ++x) {
    numbers[x] = 0;
    current[x] = 0;
  }

  // read the input stream
  for(x = 0; x < MAX; ++x) {
    cin >> input;
    if( cin.eof() ) {
      break;
    }
    numbers[x] = input;
  }

  min = MAX;
  y = 0;
  // x = number of possible items
  while( true ) {
    // if we have gone beyond the array
    if ( y >= x ) {
      break;
    }
    y = inc_array(current, x);
    min = find_min(numbers, current, x, min);
  }

  cout << "Minimum needed: " << min << endl;

  for( y = 0; y < MAX; ++y ) {
    current[y] = 0;
  }

  total = 0;
  y = 0;
  // x = number of possible items                                                             
  while( true ) {
    // if we have gone beyond the array                                                       
    if ( y >= x ) {
      break;
    }
    y = inc_array(current, x);
    total += working_combo(numbers, current, x, min);
  }


  cout << "Total combinations found: " << total << endl;

  return 0;
}

int inc_array(int current[MAX], int count) {
  int x;
  for( x = 0; x < count; ++x ) {
    if( current[x] == 0) {
      current[x] = 1;
      return x;
    }
    current[x] = 0;
  }
  return x;
}

int working_combo(int numbers[MAX],int current[MAX], int count, int min) {
  int total = 0;
  int number = 0;

  // Get array sum
  for(int y = 0; y < count; ++y) {
      total += current[y] * numbers[y];
      number += current[y];
      // cout << current[y] * numbers[y] << " ";
  }
  // cout << endl;

  if( total == GOAL ) {
    if( number == min ) {
      return 1;
    }
  }
  return 0;
}

int find_min(int numbers[MAX],int current[MAX], int count, int min) {
  int total = 0;
  int number = 0;

  for(int y = 0; y < count; ++y) {
    total += current[y] * numbers[y];
    number += current[y];
    // cout << current[y] * numbers[y] << " ";                                              
  }
  // cout << endl;                                                                            

  if( total == GOAL ) {
    if(number < min ) {
      return number;
    }
  }
  return min;
}
