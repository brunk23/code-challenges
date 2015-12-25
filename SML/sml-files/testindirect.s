; This will read in 3 numbers and print them backwards.
; This is a simple implementation of a stack or array
; the bottom half is the index and top half is the address
110 016		; Read into the address pointed at by 016
060 016		; increment 16
110 016		
060 016
110 016
111 016		; Print from the address pointed at by 16
061 016		; decrement 16
111 016
061 061
111 016
430 00		; quit
0
0
0
0
0
060 000		; 16 points to 60 + 000
