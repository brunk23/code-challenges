#include <iostream>

using namespace std;

int sumOfMultiples(int,int);

int main()
{
  cout << "The sum of the multiples of 3 and 5 below 1000 is "
       << (sumOfMultiples(3,999) +
	   sumOfMultiples(5,999) -
	   sumOfMultiples(15,999))
       << endl;

  return 0;
}


int sumOfMultiples(int fact, int to)
{
  to /= fact;
  
  return fact*to*(to+1)/2;
}
  
