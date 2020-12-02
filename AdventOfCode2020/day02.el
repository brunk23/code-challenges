;; Needed for BOTH
(defun daydata (file)
  "Read file into list of strings, one string per line."
  (with-current-buffer (find-file-noselect file)
    (split-string
     (save-restriction
       (widen)
       (buffer-substring-no-properties
	(point-min)
	(point-max)))
     "\n" t)))

;; Needed for part A
(defun isvalidp (passwd)
  "Will return t, if the passwd is valid according to part a rules."
  (let* ((fields (split-string passwd " "))
	 (range (mapcar 'string-to-number (split-string (car fields) "-")))
	 (char (elt (elt fields 1) 0))
	 (pstr (elt fields 2))
	 (len (length pstr))
	 (count 0)
	 (current 0))
    (while (< current len)
      (if (= char (elt pstr current))
	  (setq count (+ 1 count)))
      (setq current (+ 1 current)))
    (if (and (>= count (elt range 0)) (<= count (elt range 1)))
	t
      nil)))

;; Needed for part B
(defun isvalidp (passwd)
  "Will return t, if the passwd is valid according to part b rules."
  (let* ((fields (split-string passwd " "))
	 (range (mapcar 'string-to-number (split-string (car fields) "-")))
	 (char (elt (elt fields 1) 0))
	 (pstr (elt fields 2))
	 (len (length pstr))
	 (count 0)
	 (current 0))
    (if (and (= char (elt pstr (- (elt range 0) 1)))
	     (not (= char (elt pstr (- (elt range 1) 1)))))
	t
      (if (and (= char (elt pstr (- (elt range 1) 1)))
	       (not (= char (elt pstr (- (elt range 0) 1)))))
	  t
	nil))))

;; Needed for BOTH
(defun process (pfile)
  "This will process the data list and count the valid passwords."
  (let ((nvalid 0))
    (dolist (passwd pfile)
      (if (isvalidp passwd)
	  (setq nvalid (+ 1 nvalid))))
    (message "Valid passwords: %d" nvalid)))

;; Use the real data FOR ACTUAL
(setq inp (daydata "./day02.input"))

;; Use the sample data FOR TESTING
(setq inp '("1-3 a: abcde" "1-3 b: cdefg" "2-9 c: ccccccccc"))

;; This will perform the actual work
(process inp)
