#include <iostream>
#include <string>
#include <map>

#define LINES 968

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

long first(long commands[LINES]);

int main(int argc, char *argv[]) {
  long count=0,tmp;
  long commands[LINES];
  string buff;

  while(getline(cin,buff)) {
    tmp = 0;
    for(int i=1; i < buff.length(); i++) {
      tmp *= 10;
      tmp += buff[i] - '0';
    }
    if( buff[0] == '+' ) {
      commands[count] = tmp;
    } else {
      commands[count] = -tmp;
    }
    count++;
  }

  cout << first(commands) << endl;
  
  return 0;
}

/*
 * I use std::map, because of the problems with speed with my other
 * data structure (an array of all values). I am not super familiar
 * with map and should learn more about it.
 */
long first(long commands[LINES]) {
  long count = 0;
  int i;
  std::map<long, long> exists;

  while( true ) {
    for(i = 0; i < LINES; i++) {
      count += commands[i];
      if( exists.count(count) > 0 ) {
	return count;
      }
      exists.insert(std::make_pair(count, count));
    }
  }
}
