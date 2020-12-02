;; Read the data file into a list, one string per line
(defun daydata (file)
  (with-current-buffer (find-file-noselect file)
    (split-string
     (save-restriction
       (widen)
       (buffer-substring-no-properties
	(point-min)
	(point-max)))
     "\n" t)))

;; Use the real data
(setq inp (daydata "./day02.input"))

;; Use the sample data
(setq inp '("1-3 a: abcde" "1-3 b: cdefg" "2-9 c: ccccccccc"))
