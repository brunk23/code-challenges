;; Default function to read in the day's data file
(defun loaddaydata (file)
  "Read file into list of strings, one string per line."
  (with-current-buffer (find-file-noselect file)
    (split-string
     (save-restriction
       (widen)
       (buffer-substring-no-properties
	(point-min)
	(point-max)))
     "\n" nil)))

(defun sample ()
  (split-string "abc

a
b
c

ab
ac

a
a
a
a

b
" "\n" nil))

(defun sumcounts (counts)
  "Will count the number of non-zero elements in the vector."
  (let ((sum 0)
	(curr 0))
    (while (< curr 26)
      (if (> (aref counts curr) 0)
	  (setq sum (1+ sum)))
      (setq curr (1+ curr)))
    (message "%d" sum)
    sum))

(defun countchars (str count)
  "Will note if a character is in a string."
  (let ((curr 0)
	(chr 0)
	(max (length str)))
    (while (< curr max)
      (setq chr (- (elt str curr) ?a))
      (aset count chr 1)
      (setq curr (1+ curr)))
    count))

(defun andcounts (a b)
  "Return vector of matches"
  (let ((curr 0))
    (while (< curr 26)
      (aset a curr (logand (aref a curr) (aref b curr)))
      (setq curr (1+ curr)))
    a))

(defun sumallgroupyes (inp)
  "Will process the data and sum all the groups where everyone said yes."
  (let ((counts (make-vector 26 1))
	(curr 0)
	(sum 0)
	(max (length inp)))
    (while (< curr max)
      (if (< 0 (length (elt inp curr)))
	  (setq counts
		(andcounts counts
			   (countchars (elt inp curr) (make-vector 26 0))))
	(progn
	  (setq sum (+ sum (sumcounts counts)))
	  (setq counts (make-vector 26 1))))
      (setq curr (1+ curr)))
    sum))

(defun sumgroupyes (inp)
  "Will process the data and sum all the groups where anyone said yes"
  (let ((counts (make-vector 26 0))
	(curr 0)
	(sum 0)
	(max (length inp)))
    (while (< curr max)
      (if (< 0 (length (elt inp curr)))
	  (setq counts (countchars (elt inp curr) counts))
	(progn
	  (setq sum (+ sum (sumcounts counts)))
	  (setq counts (make-vector 26 0))))
      (setq curr (1+ curr)))
    (setq sum (+ sum (sumcounts counts)))
    sum))

(defun part1 (data)
  (sumgroupyes data))

(defun part2 (data)
  (sumallgroupyes data))

(part1 (sample))
(part1 (loaddaydata "./day06.input"))

(part2 (sample))
(part2 (loaddaydata "./day06.input"))
