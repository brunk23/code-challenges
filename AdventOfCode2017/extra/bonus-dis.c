/*
 * The C-ish code below is the decoded version of
 * the RISC program listed below
 *
 * Line      1	set b 86
 * Line      2	set c b
 * Line      3	set f 17
 * Line      4	jnz a 2
 * Line      5	jnz 1 10
 * Line      6	set a 10
 * Line      7	set g 0
 * Line      8	sub g c
 * Line      9	sub b g
 * Line     10	set g 0
 * Line     11	sub g b
 * Line     12	sub c g
 * Line     13	sub a 1
 * Line     14	jnz a -7
 * Line     15	set h 1
 * Line     16	set g 0
 * Line     17	sub g h
 * Line     18	sub h g
 * Line     19	sub f 1
 * Line     20	jnz f -4
 * Line     21	sub h 1
 * Line     22	set d 1
 * Line     23	set e c
 * Line     24	sub f -1
 * Line     25	set g h
 * Line     26	sub g f
 * Line     27	jnz g 2
 * Line     28	sub f h
 * Line     29	set g d
 * Line     30	sub g e
 * Line     31	jnz g 2
 * Line     32	jnz 1 3
 * Line     33	sub e 1
 * Line     34	jnz 1 -10
 * Line     35	set g b
 * Line     36	sub g d
 * Line     37	jnz g 2
 * Line     38	jnz 1 3
 * Line     39	sub d -1
 * Line     40	jnz 1 -17
 */

/* Lines 1-2 */
b = 86;
c = b;

/*
 * Lines 4-14
 *
 * This generates successive Fibonacci number
 * factors.  Before we enter the loop we have
 * #| b*=  | c*=
 * 0: x  1 | x  1
 * 1: x  2 | x  3
 * 2: x  5 | x  8
 * 3: x 13 | x 21
 * 4: x 34 | x 55
 * 5: x 89 | x144
 * 6: x233 | x377
 * 7: x610 | x987
 * 8: ...  | ...
 */
if( a != 0 ) {
  for(a = 10; a > 0; a-- ) {
    b += c;
    c += b;
  }
 }
/* This has the following effect
 * Sets b = 941356 (10946 * 86)
 * Sets c = 1523146 (17711 * 86)
 */

/*
 * Lines 3, 15-21
 *
 * Sets h = 2^17 - 1 = 131071
 */
h = 1;
for( f = 17; f > 0; f--) {
  h += h;
 }
h--;

/*
 * Lines 22-40
 *
 * Inner loop is f += c + 1 - d
 * c and 1 are constant and d goes
 * from 1 to b. It's a triangular number
 *
 * (Finds b*(c+1) - Triangle(b)) mod h
 * O(1) expr: (b * (2 * c - b + 1)) / 2 % h
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
