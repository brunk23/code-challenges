#include <stdio.h>
#include <string.h>

#include "compiler.h"

/*
 * This will process functions and built-ins
 */
int process_functions(char *n, struct Token *curr) {
  printf("%s\n",n);
  if(strcmp(n,"defun") == 0) {
    printf("defun found on line\n");
  }
  if(strcmp(n,"let") == 0) {
    printf("let found on line\n");
  }
  if(strcmp(n,"print") == 0) {
    printf("print found on line\n");
  }
  return 0;
}
