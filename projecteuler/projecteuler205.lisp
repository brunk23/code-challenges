;; This is the ugliest code I've written yet.  But, it does solve problem
;; 205.

(defun dice-sum (array faces &optional (a 1) (b 1) (c 1)
			       (d 1) (e 1) (f 1) (g 0) (h 0) (i 0) (count 0))
  (if (> i faces)
      (dice-sum array faces a b c d e f g (1+ h) 1 count)
      (if (> h faces)
	  (dice-sum array faces a b c d e f (1+ g) 1 i count)
	  (if (> g faces)
	      (dice-sum array faces a b c d e (1+ f) 1 h i count)
	      (if (> f faces)
		  (dice-sum array faces a b c d (1+ e) 1 g h i count)
		  (if (> e faces)
		      (dice-sum array faces a b c (1+ d) 1 f g h i count)
		      (if (> d faces)
			  (dice-sum array faces a b (1+ c) 1 e f g h i count)
			  (if (> c faces)
			      (dice-sum array faces a (1+ b) 1 d e f g h i count)
			      (if (> b faces)
				  (dice-sum array faces (1+ a) 1 c d e f g h i count)
				  (if (> a faces)
				      (setf (aref array 0) count)
				      (progn
					(setf (aref array (+ a b c d e f g h i))
					      (1+ (aref array (+ a b c d e f g h i))))
					(dice-sum array faces a b c d e (if (= 0 i) (1+ f) f) g h (if (> i 0) (1+ i) i) (1+ count)))))))))))))

;; This is where the main code begins

(defun main ()
  (let ((peter)
	(colin)
	(y 0)
	(n))
    (setf peter (make-array 37 :initial-element 0 :element-type 'integer))
    (setf colin (make-array 37 :initial-element 0 :element-type 'integer))
    (dice-sum peter 4 1 1 1 1 1 1 1 1 1)
    (dice-sum colin 6)
    
    ;; y=0
    ;; while x < 37
    ;; if colin[x]
    ;; y += (colin[x]/[colin[0])* sum(peter[x+1]->peter[36])/peter[0]
    
    (dotimes (x 36)
      (if (> (aref colin (1+ x)) 0)
	  (progn
	    (setf n 0)
	    (dotimes (z (- 35 x))
	      (setf n (+ n (aref peter (+ x 2 z)))))
	    (setf y (+ y (* (/ (aref colin (1+ x)) (aref colin 0)) (/ n (aref peter 0))))))))
    (format t "~A -> ~A~%" y (* 1.0 y))))
