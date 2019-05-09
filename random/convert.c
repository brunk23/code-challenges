/*
 * feed this with:
 *   hexdump -d file.bin | ./convert
 */

#include <stdlib.h>
#include <stdio.h>

int main() {
	char inbuffer[80];
	char *next;
	int output, n;

	printf("Word#:\n");
	while( (next = fgets(inbuffer, 80, stdin)) ) {
		for( n = 0; n < 9; n++ ) {
			if( n ) {
				output = strtol(next, &next, 10);
				printf("\t%05i", output);
			} else {
				output = strtol(next, &next, 16);
				printf("%05i:", output/2);
			}
		}
		printf("\n");
	}
	return 0;
}
