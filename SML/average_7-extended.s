# Part 1, input the data
# This will read in 7 values to the end of memory 93-99
00	: 10 99		<- (read 99)
01	: 20 09		<- (load 2000)
02	: 30 00		<- (add 00)
03	: 21 05		<- (store add inst at 05)
04	: 20 19		<- (load sum)
05	: 00 00		<- (add current value)
06	: 21 19		<- store in sum
07	: 61 00		<- (dec 00)
08	: 60 20		<- (inc numbers)
09	: 20 00		<- (load read instruction)
10	: 31 18		<- (subtract count)
11	: 42 13		<- (branch zero 14)
12	: 40 00		<- (go back to start)

# Part 4, compute and display average then HALT
13	: 20 19		<- (load sum)
14	: 32 20		<- (divide numbers)
15	: 21 21		<- (store average)
16	: 11 21		<- (print average)
17	: 43 00		<- (halt machine)

# Data Area
18	: 10 92		<- (99-7=92 :: 99-n=?? for other amounts n<76)
19	: 00 00		<- (sum)
20	: 00 00		<- (numbers)
21	: 00 00		<- (average)
