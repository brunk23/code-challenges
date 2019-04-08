#include "global.h"
#include <stdlib.h>

void error(char *m) {
  fprintf(stderr, "line %d: %s\n", lineno, m);
  exit(1);
}
