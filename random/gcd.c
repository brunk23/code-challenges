#include <stdio.h>
#include <stdlib.h>

int getint(const char *);

/* Finds and returns the greatest common divisor of two integers.
   Uses Euclid's algorithm: divides the larger integer by the
   smaller: if the remainder is 0, the smaller integer is the GCD,
   otherwise the smaller integer becomes the larger integer, the
   remainder becomes the smaller integer, and the process is
   repeated. Avoids code recursion. 
*/

unsigned int gcd(unsigned int int1, unsigned int int2);

unsigned int gcd(unsigned int int1, unsigned int int2) {
  unsigned int temp;

  /* swap if necessary to make sure that int1 >= int2 */
  if( int1 < int2 ) {
    temp = int1;
    int1 = int2;
    int2 = temp;
  }

  /* Now loop, dividing int1 by int2 and checking the remainder,
     until the remainder is 0. At each step, if the remainder isn't
     0, assign int2 to int 1, and the remainder to int2, then repeat
  */
  for(;;) {
    /* If the remainder of int1 divided by int2 is 0, then int2 is
       the gcd */
    if( (temp = int1 % int2) == 0) {
      return(int2);
    }
    
    /* Make int2 the larger integer and the remainder the
       smaller integer, and repeat the process */
    int1 = int2;
    int2 = temp;
  }
}


/* driver for testing the gcd program */
int main() {
  int a, b;

  a = getint("Input 1: ");
  b = getint("Input 2: ");

  printf("%i\n", gcd(a,b) );
 

  return 0;
}

/*
 * A function to get integer inputs in a reliable manner
 */
int getint(const char *prompt) {
  int x, num, n;

  for(n = 0; n < 3; ++n) {
    printf("%s",prompt);
    num = scanf("%i",&x);

    /* The next two lines discard the rest of the line,
       just in case we had a bad input */
    scanf("%*[^\n]");
    scanf("%*1[\n]");

    /* If we read a number, return it */
    if(num == 1) {
      return x;
    }

    /* Check to see if we got an EOF */
    if(num == EOF) {
      fprintf(stdout,"ERROR: End of file\n");
      exit(1);
    }

    /* Let the user know it was bad input */
    printf("That's not a number. Try again.\n");
  }

  /* We only get here if we have multiple bad input attempts */
  fprintf(stderr,"ERROR: Three failed input attempts\n");
  exit(1);
}
