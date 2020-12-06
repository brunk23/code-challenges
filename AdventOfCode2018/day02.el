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
  '("abcdef" "bababc" "abbcde" "abcccd" "aabcdd" "abcdee" "ababab"))

(defun sample2 ()
  '("abcde" "fghij" "klmno" "pqrst" "fguij" "axcye" "wvxyz"))

(defun countletters (str)
  "Count how many of each letter there are."
  (let ((curr 0)
	(c 0)
	(cnt (make-vector 26 0))
	(max (length str)))
    (while (< curr max)
      (setq c (- (elt str curr) ?a))
      (aset cnt c (1+ (aref cnt c)))
      (setq curr (1+ curr)))
    cnt))

(defun 2and3 (alp)
  "Does alp contain exactly two or exactly three of a char."
  (let ((two 0)
	(three 0)
	(curr 0))
    (while (< curr 26)
      (if (= 2 (aref alp curr)) (setq two 1))
      (if (= 3 (aref alp curr)) (setq three 1))
      (setq curr (1+ curr)))
    (list two three)))

(defun checksum (data)
  "Return product of strings that have two and three chars"
  (let ((curr 0)
	(max (length data))
	(twos 0)
	(threes 0)
	result)
    (while (< curr max)
      (setq result (2and3 (countletters (elt data curr))))
      (setq twos (+ twos (elt result 0)))
      (setq threes (+ threes (elt result 1)))
      (setq curr (1+ curr)))
    (* twos threes)))

(defun onediffp (str1 str2)
  "Determine if two strings have exactly one difference."
  (let ((max (min (length str1) (length str2)))
	(num 0)
	(curr 0))
    (while (and (< curr max) (< num 2))
      (if (not (= (elt str1 curr) (elt str2 curr)))
	  (setq num (1+ num)))
      (setq curr (1+ curr)))
    (and (= 1 num) (= (length str1) (length str2)))))

(defun trim (s1 s2)
  "Get rid of the one different character"
  (let ((max (length s1))
	(curr 0))
    (while (< curr max)
      (if (not (= (elt s1 curr) (elt s2 curr)))
	  (message "%s" (concat
			 (substring s1 0 curr)
			 (substring s1 (1+ curr) max))))
      (setq curr (1+ curr)))))

(defun findonediff (data)
  "Find the strings with one difference, print trimmed."
  (let ((max (length data))
	(curr 0)
	next
	str)
    (while (< curr max)
      (setq next (1+ curr))
      (setq str (elt data curr))
      (while (< next max)
	(if (onediffp str (elt data next))
	    (trim str (elt data next)))
	(setq next (1+ next)))
      (setq curr (1+ curr)))))

(defun part1 (data)
  (checksum data))

(defun part2 (data)
  (findonediff data))

(part1 (sample))
(part1 (loaddaydata "./day02.input"))

(part2 (sample2))
(part2 (loaddaydata "./day02.input"))
