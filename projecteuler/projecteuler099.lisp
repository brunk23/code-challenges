;; This compares very large numbers of x^y by using y*ln(x) as the
;; relative values will be the same.  As the answer has over 3 million
;; digits, this is a faster way.

(defun process-file ()
  (with-open-file (file-of-base-exp
		   "~/src/projecteuler/p099_base_exp.txt"
		   :direction :input :if-does-not-exist :error)
    (do ((line (read-line file-of-base-exp nil)
	       (read-line file-of-base-exp nil))
	 (count 1 (1+ count))
	 (current-value 0)
	 (best-line 0))
	((null line) best-line)
      ;;	(if (= 709 count)
      ;;	    (print (list count (value-of-line line))))
      (if (> (value-of-line line) current-value)
	  (progn
	    (setq current-value (value-of-line line))
	    (setq best-line count))))))

(defun value-of-line (line)
  (let ((ba 0) (ex 0))
    (multiple-value-setq (ba ex) (read-from-string line t nil))
    (setq ex (read-from-string line t nil :start (1+ ex)))
    (* ex (log ba))))
