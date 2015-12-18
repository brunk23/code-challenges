(defun factorial (x &optional (sum 1))
  (if (> 2 x)
      sum
      (factorial (1- x) (* sum x))))

;; Using the lookup table gives a 35,500% increase in speed
;; (355.45x faster)... less than 1/25th of a second, compared to
;; almost 13 seconds otherwise.
(defun dig-fact (x)
  (nth x '(1 1 2 6 24 120 720 5040 40320 362880)))

(defun digit-factorial-sum (x &optional (sum 0))
  (if (< x 9)
      (+ sum (dig-fact x))
      (digit-factorial-sum (/ (- x (mod x 10)) 10)
			   (+ sum (dig-fact (mod x 10))))))

(defun sum-dig-fact-sum ()
  (do ((x 3 (1+ x))
       (y 0))
      ((< 50000 x) y)
    (if (= x (digit-factorial-sum x))
	  (setq y (+ y x)))))

(defun sum-all-digits (x &optional (sum 0))
  (if (< x 10)
      (+ sum x)
      (sum-all-digits (/ (- x (mod x 10)) 10) (+ sum (mod x 10)))))

;; What is the maximum sum of the digits of all the results a^b
;; where a and b are all numbers between 1 and 99.
(defun maximal-digit-sum ()
  (let ((max 0))
    (do ((x 1 (1+ x)))
	((> x 99) max)
      (do* ((y 1 (1+ y))
	   (test (sum-all-digits (expt x y)) (sum-all-digits (expt x y))))
	  ((> y 99))
	(if (< max test)
	    (setq max test))))))

(defun problem-48 ()
  (do ((x 1 (1+ x))
       (y 0 (mod (+ y (expt x x)) (expt 10 10))))
      ((> x 1000) (mod y (expt 10 10)))))

(defun A-problem-282 (m n)
  (let ((st-m (cons m '()))
	(st-n (cons n '())))
    (loop
       (when (and (= (car st-m) 0) (= 1 (length st-m) 0))
	 (return (1+ (car st-n))))
       (if (= (car st-m) 0) (setq st-n (cons (1+ (car st-n)) (cdr st-n))))
       (if (= 0 (car st-n))
	   (progn
	     (setq st-m (cons (1- (car st-m)) (cdr st-m)))
	     (setq st-n (cons 1 (cdr st-n))))
	   (progn
	     (setq st-m (cons (1- (car st-m)) (cdr st-m)))
	     (setq st-m (cons (1+ (car st-m)) st-m))
	     (setq st-n (cons (1- (car st-n)) st-n)))))))

(defun sum-ack ()
  (do ((x 0 (1+ x))
       (sum 0 (mod (+ sum (a-problem-282 x x)) (expt 14 8))))
      ((> x 6) sum)))
    
