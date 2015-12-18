;; (* 6 (expt 9 5)) = 354294 ... we only need to check 6 digit numbers.
;; Numbers of seven digits won't have 5th power sums of all their digits.
;; We must start at 000002 not 000000 because 1^5 isn't a sum and doesn't
;; count.  This code is ugly.  But it does work.

(defun sum-5th-power (&optional (a 0) (b 0) (c 0) (d 0) (e 0) (f 2) (sum 0))
  (format t "~A:~A:~A:~A:~A:~A :: ~A~%" a b c d e f sum)
  (if (= 3 a)
      sum
      (sum-5th-power
       (cond ((= 10 f) a b c d (1+ e) 0)
	     ((= 10 e) a b c (1+ d) 0 0)
	     ((= 10 d) a b (1+ c) 0 0 0)
	     ((= 10 c) a (1+ b) 0 0 0 0)
	     ((= 10 b) (1+ a) 0 0 0 0 0)
	     (t (1+ f) e d c b a))
       (if (= (+ (expt a 5) (expt b 5) (expt c 5)
		 (expt d 5) (expt e 5) (expt f 5))
	      (+ (* a 100000) (* b 10000) (* c 1000)
		 (* d 100) (* e 10) f))  
	   (+ sum (* a 100000) (* b 10000) (* c 1000)
	      (* d 100) (* e 10) f)
	   sum))))
