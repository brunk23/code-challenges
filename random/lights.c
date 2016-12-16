#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LIGHTSDEFAULT 1000
#define OFF '-'
#define ON 'O'

void fliplights(char *, int);
void initializestring(char *, int);
void printstring(char *, int);
void lightson(int);
void showlights(int);

/*
 * Flip the state of the lights which are multiples of mult
 */
void fliplights(char *lightstring, int mult) {
  int n = 0;
  while(0 != lightstring[n]) {
    if( 0 == ( (n+1) % mult ) ) {
      if( lightstring[n] == ON ) {
	lightstring[n] = OFF;
      } else {
	lightstring[n] = ON;
      }
    }
    ++n;
  }
}

/*
 * Make a string with all lights off.
 */
void initializestring(char *n, int i) {
  int j;
  for( j = 0; j < i; ++j ) {
    n[j] = OFF;
  }
  n[j] = 0;
}

/*
 * Print the string for normal mode
 */
void printstring(char *n, int time) {
  printf("%5i: %s\n", time, n);
}

/*
 * Just print which lights and the answer
 */
void lightson(int n) {
  int i = 1, x;

  printf("Lights on: {");
  x = i * i;
  while ( x <= n ) {
    printf(" %i", x);
    ++i;
    x = i * i;
  }
  printf("} Total: %i\n", i-1);
}

void showlights(int lights) {
  int n = 0;
  char *lightstring;

  lightstring = (char *)malloc( sizeof(char) * lights + 1 );

  initializestring(lightstring, lights);
  
  while ( n <= lights ) {
    printstring( lightstring, n );
    sleep(1);
    ++n;
    fliplights( lightstring, n );
  }
}

int main(int argc, char *argv[]) {
  int lights = LIGHTSDEFAULT;

  if ( argc > 1 ) {
    /*
     * Just print which lights are on.
     */
    lights = (int)strtol(argv[1], (char **)NULL, 10);

    if( lights < 1 ) {
      lights = LIGHTSDEFAULT;
    }

    lightson(lights);
  } else {
    showlights(lights);
  }

  return 0;
}
