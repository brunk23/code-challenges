# It appears that a + 643*4 must produce remainders of
# 0 then 1, over and over exactly ending with 1.


function output(a) {
	
	d = a
        c = 4
 	d = a + 643 * 4
     	
L9-->   a = d
L10-->  b = a
	a = 0

L13--> 	c = 2
L14--> 	jnz b L16
    	goto L21
L16---> b--
    	c--
    	jnz c L14
        a++
    	goto L13
L21-->  b = 2     ( a = (a + 643*4)/2  -- c = 2 when even, 1 odd) 
L22--> 	jnz c L24
    	goto L27
L24-->  b--
    	c--
    	goto L22
L27-->
    	out b
    	jnz a L10
    	goto L9
