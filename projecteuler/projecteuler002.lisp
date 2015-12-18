;; Call with (sum-even-fibb 1 1 4000000) for the answer to the
;; given numbers. Will solve for any range given two starting
;; numbers from the series.

(defun sum-even-fibb (previous current stop &optional (acc 0))
  (if (> (+ previous current) stop) acc
      (if (= (mod (+ previous current) 2) 0)
	  (sum-even-fibb
	   current (+ current previous) stop (+ acc current previous))
	  (sum-even-fibb current (+ current previous) stop acc))))
