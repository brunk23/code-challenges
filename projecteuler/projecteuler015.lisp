;; A quick calculation for triangular numbers
(defun nth-triangular-number (n)
  (/ (* n (1+ n)) 2))

;; This will return the number of factors a number has. It will
;; always be even for non-square numbers and odd for square
;; numbers.  It only checks 2-sqrt(n) values.
(defun factor-count (n)
  (labels ((fact-count (limit)
	     (do ((x 2 (1+ x))
		  (count 2))
		 ((> x limit) count)
	       (if (= 0 (mod n x))
		   (if (= n (* x x))
		       (setf count (1+ count))
		       (setf count (+ 2 count)))))))
    (fact-count (sqrt n))))

;; Find the first triangular number with over min-divisors divisors
(defun divisors-exceed (&optional (min-divisors 500))
  (do ((x 2 (1+ x)))
      ((> (factor-count (nth-triangular-number x)) min-divisors)
       (nth-triangular-number x))))

;; This is not part of the challenge.  I wanted to know which locker
;; was touched the most often in the locker challenge. #840... touched
;; 32 times
(defun count-divisors (&optional (until 1000))
  (do* ((x 1 (1+ x))
       (max 1)
       (all nil)
       (factc (factor-count x) (factor-count x)))
      ((> x until) (list max all))
    (if (= factc max)
	(push x all)
	(if (> factc max)
	    (progn
	      (setf all (list x))
	      (setf max factc))))))
