b = 86;
c = b;

/*
 * Sets b = 941356
 * Sets c = 1523146
 */
if( a != 0 ) {
  for(a = 10; a > 0; a-- ) {
    b += c;
    c += b;
  }
 }

/*
 * This appears to set h = 2^17 - 1
 */
h = 1;
for( f = 17; f > 0; f--) {
  h += h;
 }
h--;

/*
 * (Finds b*(c+1) - Triangle(b)) mod h
 */
for( d = 1; d < b; d++ ) {
  for( e = c; e != d; e-- ) {
    f++;
    // zero out f, when it equals h
    // This is essentially the mod operation
    if( h == f ) {
      f -= h;
    }
  }
 }

// Combined into 1 line
  std::cout << (b * (2 * c - b + 1)) / 2 % h << std::endl;
