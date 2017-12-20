#!/bin/sh

# Paste the stats page here.  This will rank the difficulty of the
# second part of each day, by ranking the percentage of people
# who got the first part but not the second.

awk '{printf "%0.2f", 100 * $3 / ( $2 + $3 );\
	print "%\tout of\t" $2 + $3\
       	"\tonly did part one of Day " $1}' | sort -rn
