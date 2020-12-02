;; Needed for BOTH parts
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

;; Needed for BOTH parts
;; Make sure you load the correct isvalidp for the part you are answering
(defun process (pfile)
  "This will process the data list and count the valid passwords."
  (let ((nvalid 0))
    (dolist (passwd pfile)
      (if (isvalidp passwd)
	  (setq nvalid (+ 1 nvalid))))
    (message "Valid passwords: %d" nvalid)))


;; Needed for part one
(defun isvalidp (passwd)
  "Will return t, if the passwd is valid according to part one rules."
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

;; Needed for part two
(defun isvalidp (passwd)
  "Will return t, if the passwd is valid according to part two rules."
  (let* ((fields (split-string passwd " "))
	 (range (mapcar 'string-to-number (split-string (car fields) "-")))
	 (char (elt (elt fields 1) 0))
	 (pstr (elt fields 2)))
    (if (and (= char (elt pstr (- (elt range 0) 1)))
	     (not (= char (elt pstr (- (elt range 1) 1)))))
	t
      (if (and (= char (elt pstr (- (elt range 1) 1)))
	       (not (= char (elt pstr (- (elt range 0) 1)))))
	  t
	nil))))


;; Once you have loaded the three functions above according to the part
;; of the day you are on, select one of the following to get an answer.
;; You can run the next part of the day by just loading the next
;; isvalid and running this again.

;; Use the real data FOR ACTUAL ANSWER
(process (loaddaydata "./day02.input"))

;; Use the sample data FOR TESTING PURPOSES
(process '("1-3 a: abcde" "1-3 b: cdefg" "2-9 c: ccccccccc"))
