;; Given the lengths of the three sides of a triangle, this
;; function will return the area of that triangle.
(defun area-of-triangle (side-a side-b side-c)
  (if (and (> side-a 0)
	   (> side-b 0)
	   (> side-c 0)
	   (> (- (+ side-a side-b) side-c) 0)
	   (> (- (+ side-a side-c) side-b) 0)
	   (> (- (+ side-b side-c) side-a) 0))
      (let ((s (/ (+ side-a side-b side-c) 2)))
	(sqrt (* s (- s side-a) (- s side-b) (- s side-c))))
      (format t "These values don't describe a real triangle.~%")))
