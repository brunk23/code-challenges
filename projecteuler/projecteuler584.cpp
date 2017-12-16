#include <iostream>
#include <random>
#include <iomanip>

using std::cout;
using std::endl;

class Room {
private:
  int *year;			// Keep the year
  int total_days;		// How many days in a year
  int days_off;			// How many days off it can be
  int person_count;		// How many people share range
  std::random_device rd;
  std::mt19937 rnd;
  std::uniform_int_distribution<int> uni;
  
  bool add_person(int j) {
    int i;

    for( i = 0; i <= days_off; i++ ) {
      year[ (j + i) % total_days ]++;
      if( year[ (j + i) % total_days ] == person_count ) {
	return true;
      }
    }
    return false;
  }
  
public:
  Room( int annum, int range, int people ) {
    std::mt19937 rng(rd());
    uni = std::uniform_int_distribution<int>(0, annum - 1);
    
    year = new int[annum];
    total_days = annum;
    days_off = range;
    person_count = people;
    reset();
  }

  void reset() {
    int i;
    for( i = 0; i < total_days; i++ ) {
      year[i] = 0;
    }
  }
  
  bool entry() {
    int i = uni(rd);
    
    return add_person( i );
  }
  
};
  
int main() {
  long i;
  long sum = 0, trials;
  Room foo( 365, 7, 4 );

  for( trials = 1; trials <= 10000000000; trials++ ) {
    i = 1;
    while( !foo.entry() ) {
      i++;
    }
    foo.reset();
    sum += i;
    if( (trials % 100000) == 0 ) {
      cout << std::setprecision(12) << trials
	   << ": " << static_cast<double>(sum)/trials << endl;
    }
  }
  
  return 0;
}
