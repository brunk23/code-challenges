;; A program to return the total possible ways to create
;; change for a certain amount of money

(defun count-change (amount) 
  (cc amount 6))
(defun cc (amount kind-of-coins) 
  (cond ((= amount 0) 1)
	((or (< amount 0) (= kind-of-coins 0)) 0)
	(else (+ (cc amount (- kind-of-coins 1))
		 (cc (- amount 
			(first-denomination kind-of-coins))
		     kind-of-coins)))))
(defun first-denomination (kind-of-coins) 
  (cond ((= kind-of-coins 1) 1)
	((= kind-of-coins 2) 5)
	((= kind-of-coins 3) 10)
	((= kind-of-coins 4) 25)
	((= kind-of-coins 5) 50)
	((= kind-of-coins 6) 100)))
