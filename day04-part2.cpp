// Build with c++ -lcrypto day04-part1.cpp

#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include <sstream>
#include <string>
#include <openssl/md5.h>

int main()
{
  unsigned char encoded[MD5_DIGEST_LENGTH];
  string key = "ckczppom";
  string combined;
  stringstream temp;
  long number;
  
  for (number = 0; number < LONG_MAX; ++number) {
    temp.str("");
    temp << key << number;
    combined = temp.str();

    MD5( (unsigned char *) combined.c_str(), combined.size(),
	 (unsigned char *) &encoded);

    cout << combined << endl;
    if( encoded[0] == 0 && encoded[1] == 0 && (encoded[2]&0xff) == 0 ) {
      cout << combined << ": " << number << " is a match folks!" << endl;
      break;
    }
  }
  cout << endl;
  return 0;
}
