(defun reverse-number (n)
  (labels ((next (n v)
	     (if (zerop n) v
		 (multiple-value-bind (q r)
		     (truncate n 10)
		   (next q (+ (* v 10) r))))))
    (next n 0)))

(defun pal-number (n &key (verbose nil))
  (do* ((x n z)
	(y (reverse-number x) (reverse-number x))
	(z (+ x y) (+ x y)))
      ((= x y) (format t "~A~%" x))
    (if verbose (format t " ~A~%+~A~%~A~%~%" x y z))))

(pal-number 89 :verbose t)
