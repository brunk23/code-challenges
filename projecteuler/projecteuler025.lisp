(defun gen-fibb (&optional (prev 1) (curr 1) (count 2))
  (if (> (/ curr (expt 10 999)) 1)
      count
      (gen-fibb curr (+ prev curr) (1+ count))))
