;; Problem 020.  Call with (factorial-digit-sum 100)

(defun sum-digits (number &optional (sum 0))
  (if (> 10 number)
      (+ sum number)
      (sum-digits (/ (- number (mod number 10)) 10) (+ sum (mod number 10)))))

(defun factorial (number &optional (prod 1))
  (if (= 1 number)
      prod
      (factorial (1- number) (* number prod))))

(defun factorial-digit-sum (number)
  (sum-digits (factorial number)))
