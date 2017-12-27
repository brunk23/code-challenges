#!/bin/sh

# Paste the stats page here.  This will rank the difficulty of the
# second part of each day, by ranking the percentage of people
# who got the first part but not the second.

awk 'BEGIN{total = 0}{ n = 100 * $3 / ( $2 + $3 ); total = total + n;\
	printf "%0.2f", n; print "%\tout of\t" $2 + $3\
	"\tonly did part one of Day " $1}\
	END{printf "\n%s%0.2f%%\n", "Average day: ", total/25}' | sort -rn
