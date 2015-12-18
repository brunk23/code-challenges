;; A palindromic number reads the same both ways. The largest palindrome
;; made from the product of two 2-digit numbers is 9009 = 91 × 99.
;; Find the largest palindrome made from the product of two 3-digit numbers.

(defun largest-3-pal (&optional (a 999) (b 999) (largest 0))
  (if (< a 100) largest
      (largest-3-pal (if (< b 100) (1- a) a) (if (< b 100) (1- a) (1- b))
		     (if (equal (reverse (prin1-to-string (* a b)))
				(prin1-to-string (* a b)))
			 (if (> (* a b) largest)
			     (* a b)
			     largest)
			 largest))))
