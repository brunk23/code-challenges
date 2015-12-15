	10 99  (read count)
	10 97  (read input number)
	99 00  (dump 9800 is NOP -- 9900 is DUMP)
	20 97  (load new number )
	31 96  (old highest)
	41 08  (skip assign)
	20 97  (load new number)
	21 96  (save the new number to highest)
	60 98  (increment count)
	20 98  (load count)
	31 99  (subtract amount to go)
	41 01  (branch negative to 01)
	11 96  (print the new number)
	43 00  (halt)

1099
1097
9800
2097
3196
4108
2097
2196
6098
2098
3199
4101
1196
4300
