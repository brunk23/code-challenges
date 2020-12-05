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

(defun descrtoseat (str)
  (let ((row 0)
	(col 0)
	(curr 0)
	(max (length str)))
    (while (< curr max)
      (cond ((= (elt str curr) ?B) (setq row (+ (* 2 row) 1)))
	    ((= (elt str curr) ?F) (setq row (* 2 row)))
	    ((= (elt str curr) ?R) (setq col (+ (* 2 col) 1)))
	    ((= (elt str curr) ?L) (setq col (* 2 col))))
      (setq curr (1+ curr)))
    (list row col)))

(defun process (boardingpasses)
  (let ((seatlist nil)
	(curr 0)
	(max (length boardingpasses)))
    (while (< curr max)
      (setq seatlist (append seatlist (list (descrtoseat (elt boardingpasses curr)))))
      (setq curr (1+ curr)))
    seatlist))

(defun findmaxid (seatlist)
  "Given a list of seats '((2 3)(4 5)(6 7)...) will return the highest id."
  (let ((curr 0)
	(max 0)
	(id 0)
	(seat nil)
	(numpasses (length seatlist)))
    (while (< curr numpasses)
      (setq seat (elt seatlist curr))
      (setq id (+ (* (elt seat 0) 8) (elt seat 1)))
      (if (> id max) (setq max id))
      (setq curr (1+ curr)))
    max))

;; Frame out the part1 wrapper
(defun part1 (boardingpasses)
  (findmaxid (process boardingpasses)))


(part1 (sample))
(part1 (loaddaydata "./day05.input"))
