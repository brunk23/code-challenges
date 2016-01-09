#include <iostream>
#include <string>

/*
 * I "cheated" a little with this challange
 * by preprocessing the file with vi, to put
 * each name on a line by itself, stripping the
 * quotation marks, and piping it through sort.
 */

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

int namesum(string);

int main()
{
  int sum = 0, count = 0;
  string input;
  
  while( getline(cin, input) ) {
    ++count;
    sum += count * namesum(input);
  }

  cout << "The sum of the names was: " << sum << endl;

  return 0;
}

int namesum(string name)
{
  unsigned int x = 0, sum = 0;

  for( x = 0; x < name.size(); ++x ) {
    sum += name[x] - 'A' + 1;
  }

  return sum;
}
