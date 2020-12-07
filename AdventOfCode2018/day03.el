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

(defun sample () '("#1 @ 1,3: 4x4" "#2 @ 3,1: 4x4" "#3 @ 5,5: 2x2"))

(defun loc (x y)
  "Helper function for getting array location."
  (+ (* 1000 y) x))

(defun fillrect (cloth x y len width)
  "This will increment every square inch that is used."
  (let ((maxx (+ x len))
	(maxy (+ y width)))
    (while (< x maxx)
      (while (< y maxy)
	(aset cloth (loc x y) (1+ (aref cloth (loc x y))))
	(setq y (1+ y)))
      (setq y (- y width))
      (setq x (1+ x)))
    cloth))

(defun overlap (cloth x y len width)
  "This will check for a region that contains no overlaps."
  (let (olap
	(maxx (+ x len))
	(maxy (+ y width)))
    (while (< x maxx)
      (while (< y maxy)
	(if (> (aref cloth (loc x y)) 1) (setq olap t))
	(setq y (1+ y)))
      (setq y (- y width))
      (setq x (1+ x)))
    olap))

(defun process (str cloth)
  "This will fill each area in cloth."
  (let* ((keys (split-string str " " t))
	(x (string-to-number (elt (split-string (elt keys 2) "[,:]" t) 0)))
	(y (string-to-number (elt (split-string (elt keys 2) "[,:]" t) 1)))
	(len (string-to-number (elt (split-string (elt keys 3) "x" t) 0)))
	(width (string-to-number (elt (split-string (elt keys 3) "x" t) 1))))
    (fillrect cloth x y len width)))

(defun checkplan (str cloth)
  "Find the one region that does not overlap."
  (let* ((keys (split-string str " " t))
	 (x (string-to-number (elt (split-string (elt keys 2) "[,:]" t) 0)))
	 (y (string-to-number (elt (split-string (elt keys 2) "[,:]" t) 1)))
	 (len (string-to-number (elt (split-string (elt keys 3) "x" t) 0)))
	 (width (string-to-number (elt (split-string (elt keys 3) "x" t) 1))))
    (if (not (overlap cloth x y len width))
	(message "%s does not overlap." (elt keys 0)))))

(defun countoverlap (cloth)
  "Count how many square inches are part of multiple plans."
  (let ((x 0)
	(sum 0))
    (while (< x (* 1000 1000))
      (if (> (aref cloth x) 1)
	  (setq sum (1+ sum)))
      (setq x (1+ x)))
    sum))

(defun plan (data)
  "Create the original plan for the cloth."
  (let ((curr 0)
	(max (length data))
	(cloth (make-vector (* 1000 1000) 0)))
    (while (< curr max)
      (setq cloth (process (elt data curr) cloth))
      (setq curr (1+ curr)))
    cloth))

(defun nooverlap (cloth data)
  "Check every region for overlap."
  (let ((curr 0)
	(max (length data)))
    (while (< curr max)
      (checkplan (elt data curr) cloth)
      (setq curr (1+ curr)))))

(defun part1 (data)
  (countoverlap (plan data)))

(defun part2 (data)
  (nooverlap (plan data) data))

(part1 (sample))
(part1 (loaddaydata "./day03.input"))

(part2 (sample))
(part2 (loaddaydata "./day03.input"))
