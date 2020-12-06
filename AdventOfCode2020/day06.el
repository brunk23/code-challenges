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

b" "\n" nil))

(defun sumcounts (counts)
  "Will count the number of non-zero elements in the vector."
  (let ((sum 0)
	(curr 0))
    (while (< curr 26)
      (if (> (aref counts curr) 0)
	  (setq sum (1+ sum)))
      (setq curr (1+ curr)))
    sum))

(defun countchars (str count)
  "Will count the number of each characters in a string."
  (let ((curr 0)
	(chr 0)
	(max (length str)))
    (while (< curr max)
      (setq chr (- (elt str curr) ?a))
      (aset count chr (1+ (aref count chr)))
      (setq curr (1+ curr)))
    count))

(defun countallgroup (inp)
  "Will loop through the data file and sum all the groups."
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
  (countallgroup data))

(part1 (sample))
(part1 (loaddaydata "./day06.input"))
