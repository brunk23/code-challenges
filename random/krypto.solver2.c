#include <stdio.h>

int r0;
int r1;
int r2;
int r3;
int r4;
int r5;
int r6;
int r7;

int five[5];
int four[5];
int three[5];
int two[5];
int one[5];

int array[5];

int permute(int *array, int len) {
  int w;

  for( w = len-1; w >= 0; w++ ) {
    printf("%i ", array[w]);
    permute(&array[6-len], len-1);
  }
  printf("\n");
  return 0;
}

int main() {

  array[0] = 1;
  array[1] = 2;
  array[2] = 3;
  array[3] = 4;
  array[4] = 5;

  permute(array, 5);
  return 0;
}
