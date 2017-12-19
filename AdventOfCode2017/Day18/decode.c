/*
 * This will not compile. But, it is the C-ish
 * translation of what the assembly code is doing.
 */
int main() {

  /***
   * Program 0 starts by generating 127 numbers and sending
   * them to b.
   * It then goes into the read loop.
   ***/
  if( ID == 0 ) {
    a = 1;
    for( i = 31; i > 0; i-- ) {
      a = a * 2;
    }
    a--;

    p = 735;
    for( i = 127; i > 0; i-- ) {
      p = (((p * 8505) % a) * 129749 + 12345) % a;
      b = p % 10000;
      send b;
    }
  }

  /***
   * Program 1 starts here, and reads in 127 numbers.
   * It starts by reading 1 number. Then it does the
   * following. It reads a new number, and sends back
   * the larger of the original number and the new
   * number. This brings smaller numbers further down
   * in the transmission list.
   * If the numbers were not largest to smallest,
   * loop again.
   * Program 0 and 1 pass this list back and forth until
   * it has been completely sorted.
   ***/
  f = 0;
  do{
    receive a;
    for( i = 126; i > 0; i-- ) {
      receive b; 
      if( b > a ) {
	send b;
	f = 1;
      } else {
	send a;
	a = b;
      }
    }
    send a;
  }while(f);

  /*
   * This is really the halt statement. But, the
   * programs just halt when both of them are waiting
   * on input without anything to send.
   */
  do {
    receive b;
  } while(b);

  return 0;
}
