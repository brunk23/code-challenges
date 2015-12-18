;; This file contains code for problems 003, 005, 007, 010  They all
;; have something to do with primes.
;; So, I put them together.  There is no attempt
;; to make these solutions completely optimal.  For example, nth-prime could
;; be faster if it used a prime-p verson of factorize that returned t if
;; there was only 1 factor and immediately returned nil upon finding a factor
;; that was not the original number. [FIXED]

;; This will generate a list of factors
(defun factorize (number &optional (current 2) factors)
  (if (> current (sqrt number))
      (progn (if (> current 1) (push number factors))
	     factors)
      (if (= (mod number current) 0)
	  (progn (push current factors)
		 (factorize (/ number current) current factors))
	  (if (= current 2) (factorize number 3 factors)
	      (factorize number (+ current 2) factors)))))

;; This is actually the solution for problem 003.
;; Call with (greatest-prime-factor 600851475143) for the answer
(defun greatest-prime-factor (number)
  (car (factorize number)))

;; This is the solution for problem 005.
;; Call with (evenly-divisible 1 20) to show solution
(defun evenly-divisible (from to &optional factors)
  (labels
      ;; If there are more of the first factor in x than
      ;; in factors, push a copy onto factors, if not, remove
      ;; all copies of the first factor and check the next
      ((merge-lists (x factors)
	 (if (not x) factors
	     (if (> (count (car x) x) (count (car x) factors))
		 (progn
		   (push (car x) factors)
		   (merge-lists x factors))
		 (merge-lists (remove (car x) x) factors)))))
    (if (> from to)
	(reduce #'* factors)		; Return product of all factors
	(evenly-divisible (1+ from) to
			  (merge-lists (factorize from) factors)))))

;; Used by nth-prime
(defun prime-p (number &optional (current 2))
  (if (> current (sqrt number)) t
      (if (zerop (mod number current))
	  (= number current)
	  (if (= current 2) (prime-p number 3)
	      (prime-p number (+ current 2))))))
  

;; Solution for problem 007 -- Only works for 1st prime and up.
;; 0th and down just return 2.
;; Call with (nth-prime 10001)
(defun nth-prime (x)
  (if (< x 2) 2
      (labels
	  ((prime-count (current count)
	     (if (= count x)
		 current
		 (if (prime-p (+ 2 current))
		     (prime-count (+ 2 current) (1+ count))
		     (prime-count (+ 2 current) count)))))
	(prime-count 3 2))))

;; Solution for problem 010
;; Call with (sum-primes 2000000)
(defun sum-primes (number &optional (current 2) (sum 0))
  (if (> current number)
      sum
      (sum-primes number (if (= current 2) 3 (+ current 2))
		  (if (prime-p current) (+ sum current) sum))))
	  

;; Problem 123
;; Call with (prime-remainder (expt 10 10)) but it takes about 10
;; minutes to run, way over the 1 minute expectations.  There is probably
;; a smarter way to do this.
(defun prime-remainder (ceiling &optional (current 2) (number 1))
  (if (not (prime-p current))
      (prime-remainder ceiling (if (= current 2) 3 (+ current 2)) number)
      (if (< (* current current) ceiling)
	  (prime-remainder ceiling (if (= current 2) 3 (+ current 2))
			   (1+ number))
	  (if (< ceiling (mod (+ (expt (1- current) number)
				 (expt (1+ current) number))
			      (expt current 2)))
	      number
	      (prime-remainder ceiling (if (= current 2) 3
					   (+ current 2))
			       (1+ number))))))
