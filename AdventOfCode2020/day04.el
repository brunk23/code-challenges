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
  "This just returns the sample data for test runs."
  (split-string "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in" "\n" nil))

(defun seq-contains-str (seq str)
  "This is a simple test to see if a string is there"
  (let ((stat nil))
    (while seq
      (if (string= (car seq) str)
	  (progn
	    (setq stat t)
	    (setq seq nil)))
      (setq seq (cdr seq)))
    stat))

(defun hair (str)
  "This will check for valid hair."
  (message "Checking Hair: %s" str)
  (let ((n 1)
	(state t))
    (if (and (= (length str) 7) (= ?# (elt str 0)))
	(while (< n 7)
	  (if (not (or (and (<= (elt str n) ?9) (>= (elt str n) ?0))
		       (and (<= (elt str n) ?f) (>= (elt str n) ?a))))
	      (setq state nil))
	  (setq n (1+ n)))
      (setq state nil))
    state))

(defun pid (str)
  "This will check for a valid pid."
  (message "Checking PID: %s" str)
  (let ((n 1)
	(state t))
    (if (not (= (length str) 9))
	(setq state nil))
    (while (and state (< n 9))
      (if (not (and (>= (elt str n) ?0) (<= (elt str n) ?9)))
	  (setq state nil))
      (setq n (1+ n)))
    state))

(defun height (str)
  "This must determine if the height is valid between cm and inches."
  (message "Checking height: %s" str)
  (let* ((data (split-string str "[ic]" t))
	 (val (string-to-number (car data)))
	 (unit (elt data 1)))
    (if (string= unit "m")
	(if (and (<= val 193) (>= val 150))
	    t
	  nil)
      (if (string= unit "n")
	  (if (and (<= val 76) (>= val 59))
	      t
	    nil)
	nil))))

(defun eye (str)
  "This will determine if the eye color is valid."
  (message "Checking eyes: %s" str)
  (or (string= (elt passport next) "amb")
      (string= (elt passport next) "blu")
      (string= (elt passport next) "brn")
      (string= (elt passport next) "gry")
      (string= (elt passport next) "grn")
      (string= (elt passport next) "hzl")
      (string= (elt passport next) "oth")))

(defun birth (str)
  "This will check if birth year is valid."
  (message "Checking birth: %s" str)
  (and (>= (string-to-number str) 1920)
       (<= (string-to-number str) 2002)))

(defun iyr (str)
  "This will check the issue year."
  (message "Checking issue: %s" str)
  (and (>= (string-to-number str) 2010)
       (<= (string-to-number str) 2020)))

(defun expire (str)
  "This will check the expiration."
  (message "Checking expiration: %s" str)
  (and (>= (string-to-number str) 2020)
       (<= (string-to-number str) 2030)))

(defun lookpassport (passport part)
  "This checks for valid passports, part two is more strict."
  (let ((curr 0)
	(next 1)
	(max (length passport))
	(stat (and
	       (seq-contains-str passport "byr")
	       (seq-contains-str passport "iyr")
	       (seq-contains-str passport "eyr")
	       (seq-contains-str passport "hgt")
	       (seq-contains-str passport "hcl")
	       (seq-contains-str passport "ecl")
	       (seq-contains-str passport "pid"))))
    (if (= part 2)
	(while (and stat (< curr max))
	  ;; This is the part 2 lookpassport.
	  ;; It must confirm valid data.
	  (cond ((string= (elt passport curr) "byr")
		 (setq stat (birth (elt passport next))))
		((string= (elt passport curr) "iyr")
		 (setq stat (iyr (elt passport next))))  
		((string= (elt passport curr) "eyr")
		 (setq stat (expire (elt passport next))))
		((string= (elt passport curr) "hcl")
		 (setq stat (hair (elt passport next))))
		((string= (elt passport curr) "ecl")
		 (setq stat (eye (elt passport next))))
		((string= (elt passport curr) "pid")
		 (setq stat (pid (elt passport next))))
		((string= (elt passport curr) "hgt")
		 (setq stat (height (elt passport next)))))
	  (setq curr (+ curr 2))
	  (setq next (+ next 2))))
    stat))

(defun process (data part)
  "This is used for both parts and counts the valid passports."
  (let ((currpassport nil)
	(currentline 0)
	(valid 0)
	(maxline (length data)))
    (while (< currentline maxline)
      (if (> (length (elt data currentline)) 0)
	  (setq currpassport
		(append currpassport
			(split-string (elt data currentline) "[: ]" t)))
	(progn
	  (if (lookpassport currpassport part)
	      (setq valid (1+ valid)))
	  (setq currpassport nil)))
      (setq currentline (1+ currentline)))
    valid))

(defun part1 (passports)
  (process passports 1))

(defun part2 (passports)
  (process passports 2))

;; Part 1
(part1 (sample))
(part1 (loaddaydata "./day04.input"))

;; Part 2
(part2 (sample))
(part2 (loaddaydata "./day04.input"))


;; This was needed to debug some issues with part 2.
(part2 (split-string "pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
hcl:#623a2f

eyr:2029 ecl:blu cid:129 byr:1989
iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

hcl:#888785
hgt:72in byr:2001 iyr:2015 cid:88
pid:545766238 ecl:hzl
eyr:2022

iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719" "\n"))
