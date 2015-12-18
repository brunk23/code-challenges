;; Solution to problem 006.
;; Call with (diff-sum-squares 1 100)
(defun diff-sum-squares (from to)
  (labels
      ((get-sums (current sum sumsquares)
	 (if (> current to)
	     (- (expt sum 2) sumsquares)
	     (get-sums (1+ current)
		       (+ current sum)
		       (+ sumsquares (expt current 2))))))
    (get-sums from 0 0)))
