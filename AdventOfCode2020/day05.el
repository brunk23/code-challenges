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
     "\n" t)))

(defun sample ()
  "This just returns the sample data for test runs."
  '("BFFFBBFRRR" "FFFBBBFRRR" "BBFFBBFRLL"))

(defun process (boardingpasses)
  '((23 5) (34 7) (77 6) (5 36)))

(defun findmaxid (seatlist)
  "Given a list of seats '((2 3)(4 5)(6 7)...) will return the highest id."
  (let ((curr 0)
	(max 0)
	(id 0)
	(seat nil)
	(numpasses (length seatlist)))
    (while (< curr numpasses)
      (setq seat (elt seatlist curr))
      (setq id (* (elt seat 0) (elt seat 1)))
      (if (> id max) (setq max id))
      (setq curr (1+ curr)))
    max))

;; Frame out the part1 wrapper
(defun part1 (boardingpasses)
  (findmaxid (process boardingpasses)))


(part1 (sample))
