;; Find a+b+c=1000 AND a^2+b^2=c^2  a<b<c

(defun triplet (&optional (a 1) (b 2))
  (if (= (+ a b (sqrt (+ (* a a) (* b b)))) 1000)
      (reduce #'* (list a b (truncate (sqrt (+ (* a a) (* b b))))))
      (if (> (+ a b b) 1000)
	  (triplet (1+ a) (+ 2 a))
	  (triplet a (1+ b)))))
