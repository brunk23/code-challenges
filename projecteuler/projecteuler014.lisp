(defun collatz (number &optional (length 1))
  (if (= 1 number)
      length
      (collatz (if (= 0 (mod number 2))
		   (/ number 2)
		   (+ 1 (* 3 number)))
	       (1+ length))))

;; By using a cons instead of a complete list for the value pairs
;; we are able to moderately speed the program up, and completely
;; cut down on the memory usage (0 bytes consed vs 90k bytes consed)

(defun longest-chain (&optional (limit 1000000))
  (do ((number 1 (1+ number))
       (longest (cons 1 1)))                    ; (length . number)
      ((= number limit) (cdr longest))
    (if (> (collatz number) (car longest))
	(progn
	  (setf (car longest) (collatz number))
	  (setf (cdr longest) number)))))
