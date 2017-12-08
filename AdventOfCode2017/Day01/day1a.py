fs = open("day01input","r");

s = fs.read();

count = 0;
mask = len( s ) - 1;

# Use offset = 1 for part A
offset = 1;

# Use this offset for part B
#offset = (len( s ) - 1) / 2;

for i in range( 0, len( s ) - 1 ):
	if( s[ i ] == s[ (i + offset) % mask ] ):
		count += int( s[ i ] );	

print count
