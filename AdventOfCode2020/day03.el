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
  '("..##......."
    "#...#...#.."
    ".#....#..#."
    "..#.#...#.#"
    ".#...##..#."
    "..#.##....."
    ".#.#.#....#"
    ".#........#"
    "#.##...#..."
    "#...##....#"
    ".#..#...#.#"))

;; As originally written, I didn't even need to change this for
;; part 2, except to return the value and move the message out to
;; a calling function.
(defun process (grid run rise)
  "This will run through the trail and count the number of trees hit"
  (let ((trees 0)
	(fact (length (car grid)))
	(rows (length grid))
	(currentrow 0)
	(currentcol 0))
    (while (< currentrow rows)
      (if (= ?#  (elt (elt grid currentrow) currentcol))
	  (setq trees (1+ trees)))
      (setq currentrow (+ currentrow rise))
      (setq currentcol (mod (+ currentcol run) fact)))
    trees))

;; Part one is simply count the trees you hit for a fixed slope
(defun part1 (data)
  "Solve the part one problem, trees hit going down 1, right 3."
  (message "You hit %d trees!" (process data 3 1)))

;; Part two requires the product of all the trees you hit for
;; a list of given slopes.
(defun part2 (data)
  "Solve the part two problem, product of trees hit with given slopes."
  (message "The product of all the trees you hit was %d"
	   (* (process data 1 1)
	      (process data 3 1)
	      (process data 5 1)
	      (process data 7 1)
	      (process data 1 2))))

;; These are the part1 test and solution.
(part1 (sample))
(part1 (loaddaydata "./day03.input"))

;; These are the part2 test and solution.
(part2 (sample))
(part2 (loaddaydata "./day03.input"))

;; You can run and get all four solutions by loading this file like
;; listed below, if you change the path to the correct location.
;; (load "{path}/day03.el")
