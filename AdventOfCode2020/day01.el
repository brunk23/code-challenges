(setq inp
      (mapcar 'string-to-number
	      (with-current-buffer (find-file-noselect "./day01.input")
		(split-string
		 (save-restriction
		   (widen)
		   (buffer-substring-no-properties
		    (point-min)
		    (point-max)))
		 "\n" t))))

(setq inp '(1721 979 366 299 675 1456))

; Part a
(let ((list inp))
  (while list
    (setq a (car list))
    (setq list (cdr list))
    (dolist (b list)
      (if (= 2020 (+ a b))
	  (print (* a b))))))

; Part b
(let ((a 0)
      (b 0)
      (c 0))
  (while (< a (- (length inp) 2))
    (setq b (+ 1 a))
    (while (< b (- (length inp) 1))
      (setq c (+ 1 b))
      (while (< c (length inp))
	(if (= 2020 (+ (elt inp a) (elt inp b) (elt inp c)))
	    (print (* (elt inp a) (elt inp b) (elt inp c))))
	(setq c (+ c 1)))
      (setq b (+ b 1)))
    (setq a (+ a 1))))

