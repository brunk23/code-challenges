;; Will return pentagon number n
(defun pentagon-number (n)
  (/ (* n (1- (* 3 n))) 2))

;; Will return t if input is a pentagon number and
;; nil if it is not.
(defun pentagon-number-p (n)
  (if (= 0 (mod (/ (1+ (sqrt (1+ (* 24 n)))) 6) 1))
      t
      nil))

;; This will continue to increment x until we find a working value.
(defun find-back-forwards ()
  (do* ((x 1 (1+ x))
	(a (pentagon-number x) (pentagon-number x))
	(c '()))
       (c (car (sort c #'<)))  		; If c is not nil, return value
    (do* ((y (1- x) (1- y))
	  (b (pentagon-number y) (pentagon-number y)))
	 ((< y 1))
      (if (and (pentagon-number-p (+ a b))
	       (pentagon-number-p (- a b)))
	  (push (- a b) c)))))
