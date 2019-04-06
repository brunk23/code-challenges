#ifndef SYNACOR_RANDOM_H
#define SYNACOR_RANDOM_H

enum RANDOM_CONSTANTS {
  RANDOM_BUFFER_SIZE = 200
};

struct synacor_random {
  SWORD random_buffer[RANDOM_BUFFER_SIZE];
  int random_numbers_left;
} synacor_rndm;

int random_fill_buffer();
int init_random();
SWORD next_random();

#endif
