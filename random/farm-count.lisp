(defun farm-count (heads legs)
  (let ((lions (- (/ legs 2) heads)))
    (format t "Lions: ~A~%Ducks: ~A~%" lions (- heads lions))))
