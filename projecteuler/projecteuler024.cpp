#include <iostream>

using namespace std;

int swap(char *,const int,const int);
int permute(char *,const int,const int);
int rotateLeft(char *,const int,const int);

int main()
{
  char a[11] = "0123456789";
  
  permute(a,0,10);

  return 0;
}

int rotateLeft(char *a, const int start, const int n)
{
  char tmp = a[start];
  int i;
  for(i = start; i < n-1; ++i) {
    a[i] = a[i+1];
  }
  a[n-1] = tmp;
}
 
/*
 * This is fairly similar in all permutation
 * programs I've seen. It should be, it's just
 * swapping two values in memory
 */
int swap(char *a, const int i, const int j) {
  char c;
  c = a[i];
  a[i] = a[j];
  a[j] = c;
  return 0;
}

/*
 * We change a, but use b to help keep things
 * original
 * http://www.bearcave.com/random_hacks/permute.html
 * Is where I found this. I was just swapping to get
 * back, but we needed to do more.
 */
int permute(char *a, const int start, const int n )
{
  int i, j;
  static int count = 0;
  ++count;
  if( count > 1000000 ) {
    return 0;
  }
  if( count == 1000000 ) {
    cout << a << endl;
    return 0;
  }
  if( start < n ) {
    for( i = n-2; i >= start; --i ) {
      for( j = i + 1; j < n; ++j ) {
	swap(a, i, j);
	permute(a, i+1, n);
      }
      rotateLeft(a, i, j);
    }
  }
  return 0;
}
