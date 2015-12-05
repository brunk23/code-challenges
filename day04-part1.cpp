// Build with c++ -lcrypto day04-part1.cpp

#include <iostream>

using std::cout;
using std::endl;

#include <sstream>
#include <string>
#include <openssl/md5.h>

int main()
{
  unsigned char encoded[MD5_DIGEST_LENGTH];
  std::string key = "ckczppom";
  std::stringstream temp;
  std::string foo;
  long number;
  std::string combined;

  for (number = 0; number < LONG_MAX; ++number) {
    temp.str("");
    temp << number;
    foo = temp.str();
    combined = key + foo;

    MD5( (unsigned char *) combined.c_str(), combined.size(),
	 (unsigned char *) &encoded);

    cout << combined << endl;
    if( encoded[0] == 0 && encoded[1] == 0 && (encoded[2]&0xf0) == 0 ) {
      cout << combined << ": " << number << " is a match folks!" << endl;
      break;
    }
  }
  cout << endl;
  return 0;
}
