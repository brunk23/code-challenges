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

;; Each seat description is actually a binary number where the letters B and R represent
;; 1s and the letters F and L represent zeros.  The highest value bit is the first letter
;; in the description. So, we just iterate through the string, and convert it into the
;; right value by doubling and adding 1 when required.
;; Originally this created a list of rows and cols for the seats, but that was unneccessary
;; for either part of the solution, so I simplified it.
(defun descrtoseat (str)
  "This will turn each description string into a seat ID number."
  (let ((val 0)
	(curr 0)
	(max (length str)))
    (while (< curr max)
      (cond ((= (elt str curr) ?B) (setq val (+ (* 2 val) 1)))
	    ((= (elt str curr) ?F) (setq val (* 2 val)))
	    ((= (elt str curr) ?R) (setq val (+ (* 2 val) 1)))
	    ((= (elt str curr) ?L) (setq val (* 2 val))))
      (setq curr (1+ curr)))
    val))

;; Originally this created a list of lists, but we only need the seat ID numbers.
(defun process (boardingpasses)
  "This will convert the list of seat descriptions into seat ID numbers."
  (let ((seatlist nil)
	(curr 0)
	(max (length boardingpasses)))
    (while (< curr max)
      (setq seatlist (append seatlist (list (descrtoseat (elt boardingpasses curr)))))
      (setq curr (1+ curr)))
    seatlist))

;; The simplest way to find the empty seat is to sort the list and find the part
;; where it is non-contiguous. We are assured the missing number is not the first
;; or the last value, and we are assured that it is the only missing value.
(defun findmissing (seatlist)
  "This will find the missing number in the sequence, assumes missing is not first/last."
  (let* ((curr 1)
	 (sortedseats (sort seatlist '<))
	 (last (elt sortedseats 0))
	 (len (length sortedseats)))
    (while (and (< curr len) (= (elt sortedseats curr) (1+ last)))
      (setq last (elt sortedseats curr))
      (setq curr (1+ curr)))
    (1- (elt sortedseats curr))))

(defun findmaxid (seatlist)
  "Given a list of seat IDs will return the highest id."
  (let ((curr 0)
	(max 0)
	(id 0)
	(numpasses (length seatlist)))
    (while (< curr numpasses)
      (setq id (elt seatlist curr))
      (if (> id max) (setq max id))
      (setq curr (1+ curr)))
    max))

;; Frame out the part1 wrapper
(defun part1 (boardingpasses)
  (findmaxid (process boardingpasses)))

;; This is the part2 wrapper
(defun part2 (boardingpasses)
  (findmissing (process boardingpasses)))

;; Part 1 sample and actual
(part1 (sample))
(part1 (loaddaydata "./day05.input"))

;; Part 2 sample and actual
(part2 (sample))
(part2 (loaddaydata "./day05.input"))
