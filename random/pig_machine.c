/*
 * This will play the game pig. It will do human v human, human v computer,
 * and computer v computer. The computer will read in rules and play that way
 */
#include <stdio.h>
#include <stdlib.h>

enum STATES { ROLL = 1, ACCEPT };

/*
 * routine should be a function that returns ROLL/ACCEPT
 */
struct player {
  int myroll;
  int myscore;
  int mytotal;
  int opponent;
  char *name;
  int (*routine)(struct player *);   /* function that describes the play of this opponent */
};

FILE *random_dev;

/*
 * This will create a new player with a name and strategy.
 */
struct player *new_player( char *n, int (*strat)() ) {
  struct player *play;

  if( !( play = malloc( sizeof(struct player) ) ) ) {
    fprintf(stderr, "Can't create player!\n");
    exit(1);
  }
  play->myroll = 0;
  play->myscore = 0;
  play->mytotal = 0;
  play->name = n;
  play->opponent = 0;
  play->routine = strat;

  return play;
}

void init_random_dev() {
  if( !( random_dev = fopen("/dev/urandom","r") )) {
    fprintf(stderr, "Error: Can't get random numbers!\n");
    exit(1);
  }
}

void destroy_random_dev() {
  if( random_dev ) {
    fclose(random_dev);
    random_dev = 0;
  }
}

int randbetween(int a, int b) {
  unsigned int y = 0;

  if( a > b ) {
    y = a;
    a = b;
    b = y;
  }

  if( !(fread((unsigned int *)&y, sizeof(unsigned int), 1, random_dev)) ) {
    fprintf(stderr, "Failed to get random number from device.\n");
    exit(1);
  }

  y %= (b-a+1);
  y += a;

  return y;
}

struct player *game(struct player *x, struct player *y) {
  int n = 0, score, roll, rolltotal = 0, p, scores[2];
  struct player *players[2];

  players[0] = x;
  players[1] = y;
  scores[0] = 0;
  scores[1] = 0;

  while( 1 ) {
    /* We don't want to trust the values in players[n] although the routine
     * functions should not change them.
     */
    score = scores[n];
    players[n]->myroll = 0;
    roll = randbetween( 1, 6 );

    if( roll == 1 ) {
      fprintf(stdout, "%s rolled a 1. End of turn.\n",
	      players[n]->name);
      n ^= 1;
      rolltotal = 0;
      continue;
    }

    rolltotal += roll;
    players[n]->myscore = scores[n];
    players[n]->myroll = rolltotal;
    players[n]->mytotal = roll + scores[n];
    players[n]->opponent = scores[ n^1 ];

    /*
     * This is the win condition.
     */
    if( players[n]->mytotal >= 100 ) {
      break;
    }

    switch( players[n]->routine( players[n]) ) {
    case ROLL:
      /* This just falls through */
      break;
    case ACCEPT:
      scores[n] += rolltotal;
      rolltotal = 0;
      n ^= 1;
      break;
    default:
      fprintf(stdout, "%s made an illegal move. Forfeit.\n",players[n]->name);
      break;
    }
  }

  return players[n];
}

int main() {
  int values[6], n;
  init_random_dev();

  for( n = 0; n < 6; n++ ) {
    values[n] = 0;
  }

  for( n = 0; n < 1000000; n++ ) {
    values[ randbetween(1,6) - 1]++;
  }
  
  for( n = 0; n < 6; n++ ) {
   printf("%i\t", values[n]);
  }
  printf("\n");

  destroy_random_dev();
  return 0;
}
