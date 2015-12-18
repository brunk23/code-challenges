(defun is-leap-year-p (year)
  (if (= 0 (mod year 4))
      (if (= 0 (mod year 100))
	  (if (= 0 (mod year 400))
	      t
	    nil)
	t)
    nil))

(defun days-in-year (year)
  (if (is-leap-year-p year) 366 365))

(defun days-in-month (month year)
  (cond	((= month 2) (if (is-leap-year-p year) 29 28))
	((or (= month 4) (= month 6) (= month 9) (= month 11)) 30)
	(t 31)))

;; Jan 1, 1900 was a Monday.
(defun count-monday-firsts (start-month start-year end-month end-year)
  )
