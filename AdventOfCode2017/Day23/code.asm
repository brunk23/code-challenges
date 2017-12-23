	# This seems to be asking how many numbers are NOT
	# prime between 107900 - 124900 in increments of
	# 17
    	b = 107900

BB    	f = 1
    	d = 2

do{
   e = 2
   do {
    	if( d*e == b )
    	   f = 0
    	e++
    } while( e != b)
	  
	d++
 } while( d != b)

	if( f == 0 )
	   h++
    	
    	if( b == 124900 )
	  HALT
    	
   	b += 17
   	goto BB
END 	       
