;; returns 1-26 for characters A-Z and a-z, returns 0 otherwise
(defun char-value (character)
  (let ((value (position character "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			 :test #'char-equal)))
    (if value (1+ value) 0)))

;; returns the value of a string
(defun string-value (string)
  (apply #'+ (loop for char across string collect (char-value char))))

;; loops through the dictionary file, outputting words who have a
;; string value of 100.
(defun find-strings-for-value (&optional (value 100))
  (with-open-file (stream "/usr/share/dict/words")
    (do ((word (read-line stream nil)
	       (read-line stream nil)))
	((null word))
      (if (= value (string-value word)) (format t "~A~%" word)))))


