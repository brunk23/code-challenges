import sys;

# The b part is not efficient, checking both lists
# all the way through. It would be easier to check
# only items that haven't been seen already. But,
# this works as is.

suma = 0;
sumb = 0;

for line in sys.stdin:
	n = list(map(int, line.split()))
	suma += max(n) - min(n)
	for a in n:
		for b in n:
			if (a % b == 0):
				if( a/b != 1 ):
					sumb += a/b;

print("Part a: " + str(suma))
print("Part b: " + str(int(sumb)))
