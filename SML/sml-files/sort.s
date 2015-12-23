
GET_NUMBS
# read number into spot 99 - x

load		X
store		YY
branch		:sort: 
:after_sort:

# SORT:
# 	if ( y == 0 )
# 		branch GET_NUMBS
# 	if ( [99-y] > [99-y+1] )
# 		swap = [99-y+1];
# 		[99-y+1] = [99-y];
# 		y = y - 1
# 		branch to SORT

:sort: load	YY
branchzero	AFTER_SORT

load		EMPTYLOAD
subtract	y		;; create [99-y]
write		:foo:
write		:bar:
inc		:foo:
:foo:			;; Load [99-y+1]
store		WORK_B
:bar:			;; Load [99-y]
store		WORK_A
subtract	WORK_B  ;
branch_neg	AFTER_SORT ;  if [99-y+1] > [99-y] We are done

load		EMPTYSTORE
subtract	YY
write		:fizz:
write		:buzz:
inc		:buzz:
load		WORK_A
:buzz:			;; store [99-y+1]
load		WORK_B
:fizz:			;; store [99-y]
dec		YY	;; y = y -1
BRANCH		:sort:


YY	=	0000	;  (hold number of numbers)
WORK_A	=	0000	;  (hold [99-y]
WORK_B	=	0000	;  (hold [99-y+1]
EMPTYLOAD = 	2100	;  (2100 - 1 = 2099)
EMPTYSTORE = 	2200	;  (2200 - 1 = 2199)


