# This seems to be asking how many numbers are NOT
# prime between 107900 - 124900 in increments of
# 17

# We don't actually care about a. It's only used
# to skip the init of b and c when zero.  C is also
# not important, it's just the end of our loop. It
# does not change, so we don't use an assingnment

b = 107900
while( b <= 124900 ) {
   f = 1
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
   b += 17
}
