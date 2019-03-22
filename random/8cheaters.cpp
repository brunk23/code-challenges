#include <iostream>
#include <random>

#define LEN 8

using std::cout;
using std::endl;

long count_notcheated(int *p, int len) {
  long count = len;
  if( p[len - 1] == 1 || p[1] == -1 ) {
    count--;
  }
  if( p[0] == -1 || p[len - 2] == 1 ) {
    count--;
  }
  for(int i = 1; i < len - 1; i++) {
    if( p[i - 1] == 1 || p[i + 1] == -1 ) {
      count--;
    }
  }
  return count;
}

void fill_people(int *p, int len, std::mt19937 &rng) {
  int n;
  std::uniform_int_distribution<int> dist2(1,2);
  for(int i = 0; i < len; i++) {
    n = dist2(rng);
    if( n == 1 ) {
      p[i] = 1;
    } else {
      p[i] = -1;
    }
  } 
}

void reset_people(int *p, int len) {
  for(int i = 0; i < len; i++) {
    p[i] = 0;
  }
}

void print_all(int *p, int len) {
  for(int i = 0; i < len; i++) {
    cout << p[i] << ":";
  }
}

int main(int argc, char *argv[]) {
  int p[LEN];
  long total = 0, count = 0;

  std::mt19937 rng;
  rng.seed(std::random_device()());
  while( true ) {
    reset_people(p, LEN);
    fill_people(p, LEN, rng);
    count += count_notcheated(p, LEN);
    total += LEN;
    cout << count << "/" << total << ": " << static_cast<double>(100*count)/total << endl;
  }
  return 0;
}
