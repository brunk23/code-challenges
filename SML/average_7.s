# Part 1, input the data
# This will read in 7 values to the end of memory 93-99
00: 10 99  <-   (read 99)
01: 20 00  <-   (load read instruction)
02: 31 25  <-   (subtract 1)
03: 21 00  <-   (store modified read instruction)
04: 31 26  <-   (subtract 1093)
05: 42 07  <-   (branch if 0 to done)
06: 40 00  <-   (back to 00)

# Part 2, sum and count
# After we read the values, we need to add them up and
# divide by the number of numbers (we save these as 60
# and 61 so we can do more numbers later.
07: 20 27  <- (load sum)
08: 30 99  <- (add 99)
09: 21 27  <- (store sum)
10: 20 08  <- (load add instruction)
11: 31 25  <- (subtract 1)
12: 21 08  <- (store modified ad instruction)
13: 20 28  <- (load counter)
14: 30 25  <- (add 1)
15: 21 28  <- (store counter)
16: 20 26  <- (load 1093)
17: 30 01  <- (add 2000)
18: 31 08  <- (subtract add instruction)
19: 41 07  <- (branch negative 07)

# Part 3, compute and display average then HALT
20: 20 27  <- (load sum)
21: 32 28  <- (divide numbers)
22: 21 29  <- (store average)
23: 11 29  <- (print average)
24: 43 00  <- (halt machine)

# Data Area
25: 00 01  <-  (increment and decrement operator)
26: 10 92  <-  (99-7=92 :: 99-n=?? for other amounts n<70)
27: 00 00  <-  (sum)
28: 00 00  <-  (numbers)
29: 00 00  <-  (average)
