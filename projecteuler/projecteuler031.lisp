;; A program to return the total possible ways to create
;; change for a certain amount of money... this is for British currency

(defun first-denomination (kind-of-coins) 
  (cond ((= kind-of-coins 1) 1)
	((= kind-of-coins 2) 2)
	((= kind-of-coins 3) 5)
	((= kind-of-coins 4) 10)
	((= kind-of-coins 5) 20)
	((= kind-of-coins 6) 50)
	((= kind-of-coins 7) 100)
	((= kind-of-coins 8) 200)))

(defun cc (amount kind-of-coins) 
  (cond ((= amount 0) 1)
	((or (< amount 0) (= kind-of-coins 0)) 0)
	(t (+ (cc amount (- kind-of-coins 1))
		 (cc (- amount 
			(first-denomination kind-of-coins))
		     kind-of-coins)))))

(defun count-change (amount) 
  (cc amount 8))
