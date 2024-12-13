#include <stdio.h>
#include <stdlib.h>

/*
 * Solve the orb puzzle
 * Start at room [3][0]. Get to room [0][3]
 * Can't go back to start or leave exit
 */

struct ROOM {
  char operp;       /* oper or value */
  char val;
};

struct ROOM rooms[4][4];

/*
 * This describes the rooms
 */
int assign_rooms() {
  rooms[0][0].operp = 1;
  rooms[0][0].val = '*';
  rooms[1][0].operp = 0;
  rooms[1][0].val = 4;
  rooms[2][0].operp = 1;
  rooms[2][0].val = '+';
  rooms[3][0].operp = -1;
  rooms[3][0].val = 22;   /* Not actually used */
  rooms[0][1].operp = 0;
  rooms[0][1].val = 8;
  rooms[1][1].operp = 1;
  rooms[1][1].val = '*';
  rooms[2][1].operp = 0;
  rooms[2][1].val = 4;
  rooms[3][1].operp = 1;
  rooms[3][1].val = '-';
  rooms[0][2].operp = 1;
  rooms[0][2].val = '-';
  rooms[1][2].operp = 0;
  rooms[1][2].val = 11;
  rooms[2][2].operp = 1;
  rooms[2][2].val = '-';
  rooms[3][2].operp = 0;
  rooms[3][2].val = 9;
  rooms[0][3].operp = -1;
  rooms[0][3].val = 1;
  rooms[1][3].operp = 1;
  rooms[1][3].val = '*';
  rooms[2][3].operp = 0;
  rooms[2][3].val = 18;
  rooms[3][3].operp = 1;
  rooms[3][3].val = '*';
  return 0;
}

/*
 * There has got to be a better way to do this
 * But, I am going to try a random walk I lower
 * the count as I find hits that work but are too
 * long.
 *
 *  -- HIT --
 * north east (26) east north (15) west south (60)
 * east east (42) west north (31) north east (30)
 * DOOR  SUCCESS!!!
 *
 */

int main() {

  int row = 3, col = 0, orb = 22, dir = 0, count = 0, MAX = 14;
  char prev;

  assign_rooms();

  while(1) {
    while( (orb < 256 && orb > 0) && (count < MAX ) ) {
      if( row == 0 && col == 3 ) {
	printf("DOOR ");
	break;
      }
      dir = rand() % 4;
      switch (dir) {
      case 0:  /* NORTH */
	if( row == 0 ) {
	  continue;
	}
	printf("north ");
	--row;
	break;

      case 1:  /* WEST */
	if( col == 0 || (col == 1 && row == 3) ) {
	  continue;  /* Don't do back to start room */
	}
	printf("west ");
	--col;
	break;

      case 2: /* EAST */
	if( col == 3 ) {
	  continue;
	}
	printf("east ");
	++col;
	break;

      case 3: /* SOUTH */
	if ( row == 3 || (row == 2 && col == 0)) {
	  continue;  /* Don't go back to start room */
	}
	printf("south ");
	++row;
	break;
      }
      ++count;
      if( rooms[row][col].operp == 1 ) {
	prev = rooms[row][col].val;
      } else {
	switch(prev) {
	case '+':
	  orb += rooms[row][col].val;
	  break;

	case '-':
	  orb -= rooms[row][col].val;
	  break;

	case '*':
	  orb *= rooms[row][col].val;
	  break;

	default:
	  break;
	}
	printf("(%i) ",orb);
	prev = 0;
      }
    }

    if( orb == 30 && count < MAX) {
      printf(" SUCCESS!!!\n");
      break;
    } else {
      printf(" NO\n");
      orb = 22;
      count = 0;
      row = 3;
      col = 0;
    }
  }
  return 0;
}
