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


(defun process (grid)
  "This will run through the list."
  t)

;; This is the test data
(process '("..##......."
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

(process (loaddaydata "./day03.input"))
