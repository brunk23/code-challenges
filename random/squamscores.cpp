#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int print_scores(int score) {
  int woomik, durmish, match = 0;
  for(woomik = 0; woomik*17 <= score; woomik++) {
    for(durmish = 0; (durmish*11 + woomik*17) <= score; durmish++) {
      if( score == (durmish*11 + woomik*17)) {
	match++;
	cout << "Durmish: " << durmish << "\tWoomik: " << woomik << endl;
      }
    }
  }
  if( match == 0 ) {
    cout << "This is not a possible score!" << endl;
  }
  return match;
}

int main(int argc, char *argv[]) {
  int score;

  cout << "What is the current score? ";
  cin >> score;

  print_scores(score);

  return 0;
}
