#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Abandoned?  I totally forget what I started this for.
 */

/*
 * Will be a program which logs various information
 */

int main(int argc, char *argv[]) {
  char *str = 0;
  size_t linesize = 0;
  ssize_t linelen;

  printf("What is your name? ");
  linelen = getline(&str, &linesize, stdin);
  if(linelen == -1 ) {
    fprintf(stderr,"No input\n");
    exit(1);
  }
  str = strtok(str,"\n");
  printf("Hello %s\n",str);

  if(str) {
    free(str);
  }

  return 0;
}
