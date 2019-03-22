#include <iostream>
#include <fstream>
#include <string>
#include <random>

/*
 * It would be better to make this dynamic but
 * at the moment it is the current length of the words file
 */
#define LEN 99171

using namespace std;

int main(int argc, char *argv[]) {
  ifstream wordlist;
  string words[LEN];
  string tmp;
  int i,j;
  std::default_random_engine generator;
  generator.seed(random_device()());
  std::uniform_int_distribution<int> distribution(0,LEN);

  /*
   * We could use a command line argument here to open the
   * possibility of other words files
   */
  wordlist.open("/usr/share/dict/words");

  if( !wordlist ) {
    cerr << "Could not open file!\n";
    return 1;
  }
  
  i = 0;
  while( wordlist >> tmp ) {
    words[i] = tmp;
    i++;
    if( i == LEN ) {
      break;
    }
  }
  wordlist.close();

  /*
   * We could use a command line argument to allow other
   * amounts than the default of 3.
   */
  for( i = 0; i < 3; i++ ) {
    j = distribution(generator);
    cout << words[j] << " ";
  }
  cout << endl;
  
  return 0;
}
