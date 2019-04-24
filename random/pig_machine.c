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
  int n = 0, score, roll, rolltotal = 0, scores[2];
  struct player *players[2];

  players[0] = x;
  players[1] = y;
  scores[0] = 0;
  scores[1] = 0;

  n = randbetween( 0, 1 );

  while( 1 ) {
    /* We don't want to trust the values in players[n] although the routine
     * functions should not change them.
     */
    score = scores[n];
    roll = randbetween( 1, 6 );

    if( roll == 1 ) {
      fprintf(stdout, "%s rolled a 1 hand has %i. End of turn.\n",
	      players[n]->name, scores[n]);
      n ^= 1;
      rolltotal = 0;
      continue;
    }
    fprintf(stdout, "%s rolled a %i for a total of %i and %i this turn.\n",
	    players[n]->name, roll, rolltotal+roll, score+roll+rolltotal);

    rolltotal += roll;
    players[n]->myscore = scores[n];
    players[n]->myroll = rolltotal;
    players[n]->mytotal = rolltotal + scores[n];
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
      fprintf(stdout, "%s adds %i and has %i. End of turn.\n",
	      players[n]->name, rolltotal, scores[n]);
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

int always_accept(struct player *p) {
  return ACCEPT;
}

int never_accept(struct player *p) {
  return ROLL;
}

int math_strategy20(struct player *p) {
  if( p->myroll >= 20 ) {
    return ACCEPT;
  }
  return ROLL;
}

int human(struct player *p) {
  char a = '\0';
  printf("Roll (1) or Accept (2)? ");
  while( a < '1' || a > '2') {
    a = getchar();
    if( a == 'q' ) {
      exit(0);
    }
  }

  if( a == '2' ) {
    return ACCEPT;
  }
  return ROLL;
}

struct player *select_player() {
  struct player *p = NULL;
  char a = '\0';

  printf("1. Human\n2. Conservative\n3. Gambler\n4. Max Turn\n");
  printf("Which player? ");
  while( a < '1' || a > '4') {
    a = getchar();
    if ( a == 'q' ) {
      exit(0);
    }
  }
  switch( a ) {
  case '1':
    p = new_player("Human", human);
    break;
  case '2':
    p = new_player("Conservative", always_accept);
    break;
  case '3':
    p = new_player("Gambler", never_accept);
    break;
  case '4':
    p = new_player("Max Turn", math_strategy20);
    break;
  default:
    return NULL;
  }
  return p;
}

int main() {
  int values[2] = {0, 0}, n;
  init_random_dev();

  struct player *a, *b, *winner;

  a = select_player();
  b = select_player();

  for( n = 0; n < 100; n++ ) {
    winner = game( a, b );
    printf("%s won that game\n\n", winner->name);
    if( winner == a ) {
      values[0]++;
    } else {
      values[1]++;
    }
  }

  printf("%s won %i.\n",a->name, values[0]);
  printf("%s won %i.\n",b->name, values[1]);

  free(a);
  free(b);
  destroy_random_dev();

  return 0;
}
