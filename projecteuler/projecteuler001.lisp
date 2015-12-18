;; Call with (sum-3-and-5 1 1000) to get the solution for the given
;; problem. Will give the sums of all numbers that are products of
;; 3 or 5 for a given range.

(defun sum-3-and-5 (current below &optional (acc 0))
  (if (< current below)
      (if (or (= (mod current 3) 0) (= (mod current 5) 0))
	  (sum-3-and-5 (1+ current) below (+ acc current))
	  (sum-3-and-5 (1+ current) below acc))
      acc))
