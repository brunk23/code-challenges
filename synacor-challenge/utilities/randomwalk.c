#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

enum dir { north, south, west, east };

int main() {
	FILE *fp;
	int x = 0, n = 0;
	char *direction[4];
	srand(time ( 0 ));

	direction[0] = "north\n";
	direction[1] = "south\n";
	direction[2] = "west\n";
	direction[3] = "east\n";

	printf("doorway\nnorth\nnorth\nbridge\n");
	printf("continue\ndown\neast\ntake empty lantern\n");
	printf("west\nwest\npassage\nladder\n");

	fp = fopen("steps","w");

	for( n = 0; n < 20; ++n ) {
		x = rand () % 4;
		fprintf(fp,"%s",direction[x]);
		printf("%s",direction[ x ]);
	}

	fclose(fp);

	return 0;
}
