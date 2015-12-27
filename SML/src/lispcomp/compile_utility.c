#include "compile_utility.h"

/* Will return a uniq ID number each time it's called */
int getID() {
  static int ID = 1;
  ID++;
  return ID;
}
